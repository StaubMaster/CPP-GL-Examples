#include "Chunk.hpp"

#include "Graphics/Inst/Data.hpp"

#include "Noise/Perlin2D.hpp"

#include "ValueType/BoxI3.hpp"

#include "ValueType/Bool3.hpp"
#include "ValueType/VectorU3.hpp"

#include "ValueType/Undex2D.hpp"
#include "ValueType/UndexLoop2D.hpp"

#include "ValueType/Undex3D.hpp"
#include "ValueType/UndexLoop3D.hpp"

#include "Miscellaneous/Container/Binary.hpp"



Voxel &			Chunk::operator[](VectorU3 udx)			{ return Data[VectorU3::Convert(CHUNK_VALUES_PER_SIDE, udx)]; }
const Voxel &	Chunk::operator[](VectorU3 udx) const	{ return Data[VectorU3::Convert(CHUNK_VALUES_PER_SIDE, udx)]; }



Chunk::~Chunk()
{
	if (ChunkType == ChunkType::Empty)
	{
		delete Data;
	}
	else
	{
		delete[] Data;
	}
}
Chunk::Chunk()
	: Data(nullptr)
	, Index()
	, ChunkType(ChunkType::UnGenerated)
	, MainCount(0)
	, Buffer()
	, GraphicsExist(false)
	, BufferNeedsInit(false)
	, MainBufferNeedsData(false)
	, InstBufferNeedsData(false)
{ }
//void Chunk::Dispose() { }



//void Chunk::GenerateTestRotation() { }
void Chunk::GenerateGrid()
{
	Undex3D size3(CHUNK_VALUES_PER_SIDE);

	VectorI3 chunk_pos = Index * CHUNK_VALUES_PER_SIDE;

	UndexLoop3D loop3(Undex3D(), size3);
	for (Undex3D u = loop3.Min(); loop3.Check(u).All(true); loop3.Next(u))
	{
		VectorI3 voxel_idx = chunk_pos + u;
		VectorF3 voxel_pos = voxel_idx;

		VectorF3 grid_pos = voxel_pos.round(256);
		VectorF3 grid_rel = voxel_pos - grid_pos;

		if (grid_rel.length() < 4.0f) { Data[size3.Convert(u)].Value = 1; }
		if (VectorF3(grid_rel.X, grid_rel.Y, 0.0f).length() < 2.0f) { Data[size3.Convert(u)].Value = 1; }
		if (VectorF3(grid_rel.X, 0.0f, grid_rel.Z).length() < 2.0f) { Data[size3.Convert(u)].Value = 1; }
		if (VectorF3(0.0f, grid_rel.Y, grid_rel.Z).length() < 2.0f) { Data[size3.Convert(u)].Value = 1; }
	}
}
void Chunk::GeneratePerlin(const Perlin2D & noise)
{
	Point3D p3 = Index * CHUNK_VALUES_PER_SIDE;
	UndexLoop2D loop(Undex2D(), Undex2D(CHUNK_VALUES_PER_SIDE));
	for (Undex2D u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		Point2D p2(
			p3.X + u.X,
			p3.Z + u.Y
		);
	
		float val = 0.0f;
		val += noise.Calculate(p2 / 32) * 32;
		val += noise.Calculate(p2 / 16) * 16;
		val += noise.Calculate(p2 / 8) * 8;
		val += noise.Calculate(p2 / 4) * 4;
		val += noise.Calculate(p2 / 2) * 2;
		val += noise.Calculate(p2 / 1) * 1;
		val = val - p3.Y;

		for (unsigned int i = 0; i < CHUNK_VALUES_PER_SIDE; i++)
		{
			unsigned int voxel_u = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, Undex3D(u.X, i, u.Y));
			if (i > val)
			{
				Data[voxel_u].Value = 0;
			}
			else if (val - i < 1)
			{
				Data[voxel_u].Value = 2;
			}
			else
			{
				Data[voxel_u].Value = 3;
			}
		}
	}

}

void Chunk::Generate(const Perlin2D & noise)
{
	if (ChunkType != ChunkType::UnGenerated) { return; }

	if (Data == nullptr)
	{
		Data = new Voxel[CHUNK_VALUES_PER_VOLM];
	}
	for (unsigned int i = 0; i < CHUNK_VALUES_PER_VOLM; i++)
	{
		Data[i].Value = 0;
	}

	GeneratePerlin(noise);
	GenerateGrid();

	bool empty = true;
	for (unsigned int i = 0; i < CHUNK_VALUES_PER_VOLM; i++)
	{
		if (Data[i].Value != 0) { empty = false; break; }
	}
	if (empty)
	{
		delete[] Data;
		ChunkType = ChunkType::Empty;
		Data = new Voxel();
		Data -> Value = 0; // for returning
	}
	else
	{
		ChunkType = ChunkType::Filled;
	}

	if (GraphicsExist)
	{
		MainBufferNeedsData = true;
	}
}



void Chunk::GraphicsCreate()
{
	if (GraphicsExist) { return; }

	Buffer.Create();

	GraphicsExist = true;

	BufferNeedsInit = true;

	if (ChunkType == ChunkType::Filled || ChunkType == ChunkType::Empty)
	{
		MainBufferNeedsData = true;
	}
	InstBufferNeedsData = true;
}
void Chunk::GraphicsDelete()
{
	if (!GraphicsExist) { return; }

	Buffer.Delete();

	GraphicsExist = false;
}



static void DataQuad(Container::Binary<VoxelGraphics::MainData> & data, VoxelGraphics::VoxelFace face)
{
	data.Insert(face.Corn[0b00]);
	data.Insert(face.Corn[0b10]);
	data.Insert(face.Corn[0b01]);

	data.Insert(face.Corn[0b01]);
	data.Insert(face.Corn[0b10]);
	data.Insert(face.Corn[0b11]);
}

void Chunk::UpdateMainBuffer()
{
	if (!GraphicsExist) { return; }
	if (!MainBufferNeedsData) { return; }

	{
		Container::Binary<VoxelGraphics::MainData> data;

		if (ChunkType == ChunkType::Filled)
		{
			Undex3D size(CHUNK_VALUES_PER_SIDE);
			UndexLoop3D loop(Undex3D(), size);
			for (Undex3D u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
			{
				Voxel & voxel = Data[size.Convert(u)];
				if (!voxel.IsSolid())
				{
					continue;
				}

				VoxelGraphics::VoxelCube cube = voxel.ToGraphics(u);

				Voxel * nextX = Neighbours.Value(AxisDirection::NextX, u);
				Voxel * nextY = Neighbours.Value(AxisDirection::NextY, u);
				Voxel * nextZ = Neighbours.Value(AxisDirection::NextZ, u);

				Voxel * prevX = Neighbours.Value(AxisDirection::PrevX, u);
				Voxel * prevY = Neighbours.Value(AxisDirection::PrevY, u);
				Voxel * prevZ = Neighbours.Value(AxisDirection::PrevZ, u);

				if (prevX != nullptr && !(prevX -> IsSolid())) { DataQuad(data, cube.PrevX); }
				if (prevY != nullptr && !(prevY -> IsSolid())) { DataQuad(data, cube.PrevY); }
				if (prevZ != nullptr && !(prevZ -> IsSolid())) { DataQuad(data, cube.PrevZ); }

				if (nextX != nullptr && !(nextX -> IsSolid())) { DataQuad(data, cube.NextX); }
				if (nextY != nullptr && !(nextY -> IsSolid())) { DataQuad(data, cube.NextY); }
				if (nextZ != nullptr && !(nextZ -> IsSolid())) { DataQuad(data, cube.NextZ); }
			}
		}

		MainCount = data.Count();

		Buffer.Main.Change(data);
	}

	MainBufferNeedsData = false;
}
void Chunk::UpdateInstBuffer()
{
	if (!GraphicsExist) { return; }
	if (!InstBufferNeedsData) { return; }

	{
		Container::Binary<VoxelGraphics::InstData> data;

		VoxelGraphics::InstData temp;
		temp.Pos = Index * CHUNK_VALUES_PER_SIDE;
		data.Insert(temp);

		Buffer.Inst.Change(data);
	}

	InstBufferNeedsData = false;
}



void Chunk::Draw()
{
	if (!GraphicsExist) { return; }
	if (BufferNeedsInit)
	{
		Buffer.Inst.Init();
		Buffer.Main.Init();
		BufferNeedsInit = false;
	}
	UpdateMainBuffer();
	UpdateInstBuffer();
	Buffer.Draw();
}
