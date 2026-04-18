#include "Chunk.hpp"

#include "Graphics/Inst/Data.hpp"

#include "Noise/Perlin2D.hpp"
#include "Noise/Perlin3D.hpp"

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

		if (grid_rel.length() < 4.0f) { Data[size3.Convert(u)].Template = &VoxelTemplate::Orientation; }
		if (VectorF3(grid_rel.X, grid_rel.Y, 0.0f).length() < 2.0f) { Data[size3.Convert(u)].Template = &VoxelTemplate::Orientation; }
		if (VectorF3(grid_rel.X, 0.0f, grid_rel.Z).length() < 2.0f) { Data[size3.Convert(u)].Template = &VoxelTemplate::Orientation; }
		if (VectorF3(0.0f, grid_rel.Y, grid_rel.Z).length() < 2.0f) { Data[size3.Convert(u)].Template = &VoxelTemplate::Orientation; }
	}
}
void Chunk::GeneratePerlin(const Perlin2D & noise)
{
	VectorF3 p3 = Index * CHUNK_VALUES_PER_SIDE;
	UndexLoop2D loop(Undex2D(), Undex2D(CHUNK_VALUES_PER_SIDE));
	for (Undex2D u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		VectorF2 p2(
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
				Data[voxel_u].Template = nullptr;
			}
			else if (val - i < 1)
			{
				Data[voxel_u].Template = &VoxelTemplate::Grass;
			}
			else
			{
				Data[voxel_u].Template = &VoxelTemplate::Gray;
			}
		}
	}
}
void Chunk::GeneratePerlin(const Perlin3D & noise)
{
	VectorF3 pos = Index * CHUNK_VALUES_PER_SIDE;
	UndexLoop3D loop(Undex3D(), Undex3D(CHUNK_VALUES_PER_SIDE));
	for (Undex3D u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		VectorF3 p(
			pos.X + u.X,
			pos.Y + u.Y,
			pos.Z + u.Z
		);

		float val = 0.0f;
		val += noise.Calculate(p / 32.0f) / 32.0f;

		if (val > 0.0f)
		{
			Data[VectorU3::Convert(CHUNK_VALUES_PER_SIDE, u)].Template = &VoxelTemplate::Gray;
		}
		else
		{
			Data[VectorU3::Convert(CHUNK_VALUES_PER_SIDE, u)].Template = nullptr;
		}
	}
}

void Chunk::Generate(const Perlin2D & noise2, const Perlin3D & noise3)
{
	if (ChunkType != ChunkType::UnGenerated) { return; }

	if (Data == nullptr)
	{
		Data = new Voxel[CHUNK_VALUES_PER_VOLM];
	}
	for (unsigned int i = 0; i < CHUNK_VALUES_PER_VOLM; i++)
	{
		Data[i].Template = nullptr;
	}

	(void)noise2;
	(void)noise3;
	GeneratePerlin(noise3);
//	GeneratePerlin(noise2);
//	GenerateGrid();

	bool empty = true;
	for (unsigned int i = 0; i < CHUNK_VALUES_PER_VOLM; i++)
	{
		if (Data[i].Template != nullptr) { empty = false; break; }
	}
	if (empty)
	{
		delete[] Data;
		ChunkType = ChunkType::Empty;
		Data = new Voxel();
		Data -> Template = nullptr;
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



/*static void GraphicsData(Container::Binary<VoxelGraphics::MainData> & data, VoxelGraphics::VoxelFace face)
{
	data.Insert(face.Corn[0b00]);
	data.Insert(face.Corn[0b10]);
	data.Insert(face.Corn[0b01]);

	data.Insert(face.Corn[0b01]);
	data.Insert(face.Corn[0b10]);
	data.Insert(face.Corn[0b11]);
}*/

static void GraphicsData(Container::Binary<VoxelGraphics::MainData> & data, const Container::Binary<VoxelGraphics::MainData> & face, VectorU3 u)
{
	for (unsigned int i = 0; i < face.Count(); i++)
	{
		VoxelGraphics::MainData v = face[i];
		v.Pos += u;
		data.Insert(v);
	}
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
				if (voxel.Template == nullptr) { continue; }
				VoxelTemplate & voxel_template = *voxel.Template;
				GraphicsData(data, voxel_template.Here, u);
				if (Neighbours.Visible(AxisDirection::PrevX, u)) { GraphicsData(data, voxel_template.PrevX, u); }
				if (Neighbours.Visible(AxisDirection::PrevY, u)) { GraphicsData(data, voxel_template.PrevY, u); }
				if (Neighbours.Visible(AxisDirection::PrevZ, u)) { GraphicsData(data, voxel_template.PrevZ, u); }
				if (Neighbours.Visible(AxisDirection::NextX, u)) { GraphicsData(data, voxel_template.NextX, u); }
				if (Neighbours.Visible(AxisDirection::NextY, u)) { GraphicsData(data, voxel_template.NextY, u); }
				if (Neighbours.Visible(AxisDirection::NextZ, u)) { GraphicsData(data, voxel_template.NextZ, u); }
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
