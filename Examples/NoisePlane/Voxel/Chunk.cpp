#include "Chunk.hpp"
#include "ChunkValue.hpp"

#include "Graphics/Inst/Data.hpp"

#include "Noise/Perlin2D.hpp"

#include "ValueType/Bool3.hpp"
#include "ValueType/VectorU3.hpp"

#include "ValueType/Undex2D.hpp"
#include "ValueType/UndexLoop2D.hpp"

#include "ValueType/Undex3D.hpp"
#include "ValueType/UndexLoop3D.hpp"

#include "Miscellaneous/Container/Binary.hpp"



Voxel &			Chunk::operator[](VectorU3 udx)			{ return Voxels[VectorU3::Convert(CHUNK_VALUES_PER_SIDE, udx)]; }
const Voxel &	Chunk::operator[](VectorU3 udx) const	{ return Voxels[VectorU3::Convert(CHUNK_VALUES_PER_SIDE, udx)]; }



Chunk::~Chunk() { }
Chunk::Chunk()
	: Voxels()
	, Index()
	, IsGenerated(false)
	, MainCount(0)
	, Buffer()
	, GraphicsExist(false)
	, BufferNeedsInit(false)
	, MainBufferNeedsData(false)
	, InstBufferNeedsData(false)
{ }



void Chunk::Generate(const Perlin2D & noise)
{
	if (IsGenerated) { return; }

	Undex2D size2(CHUNK_VALUES_PER_SIDE);
	Undex3D size3(CHUNK_VALUES_PER_SIDE);

	Point3D pos = Point3D(Index) * CHUNK_VALUES_PER_SIDE;

	UndexLoop2D loop(Undex2D(), size2);
	for (Undex2D u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		Point2D p(
			(pos.X + u.X) * CHUNK_SCALE,
			(pos.Z + u.Y) * CHUNK_SCALE
		);
		float val = 0.0f;
		val += noise.Calculate(p / 8) * 8;
		val += noise.Calculate(p / 4) * 4;
		val += noise.Calculate(p / 2) * 2;
		val += noise.Calculate(p);
		val += noise.Calculate(p * 2) / 2;
		val += noise.Calculate(p * 4) / 4;
		val += noise.Calculate(p * 8) / 8;
		val = (val / CHUNK_SCALE) - pos.Y;
		for (unsigned int i = 0; i < CHUNK_VALUES_PER_SIDE; i++)
		{
			Undex3D u3(u.X, i, u.Y);
			if (i > val)
			{
				Voxels[size3.Convert(u3)].Value = 0;
			}
			else
			{
				Voxels[size3.Convert(u3)].Value = 1;
			}
		}
	}

	IsGenerated = true;

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

	if (IsGenerated)
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

		Undex3D size(CHUNK_VALUES_PER_SIDE);
		UndexLoop3D loop(Undex3D(), size);
		for (Undex3D u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
		{
			Voxel & voxel = Voxels[size.Convert(u)];
			if (!voxel.IsSolid())
			{
				continue;
			}

			VoxelGraphics::VoxelCube cube = voxel.ToGraphics(u);

			ChunkValue nextX = Neighbours.Value(AxisDirection::NextX, u);
			ChunkValue nextY = Neighbours.Value(AxisDirection::NextY, u);
			ChunkValue nextZ = Neighbours.Value(AxisDirection::NextZ, u);

			ChunkValue prevX = Neighbours.Value(AxisDirection::PrevX, u);
			ChunkValue prevY = Neighbours.Value(AxisDirection::PrevY, u);
			ChunkValue prevZ = Neighbours.Value(AxisDirection::PrevZ, u);

			if (!prevX.IsSolid()) { DataQuad(data, cube.Face[0]); }
			if (!prevY.IsSolid()) { DataQuad(data, cube.Face[1]); }
			if (!prevZ.IsSolid()) { DataQuad(data, cube.Face[2]); }

			if (!nextX.IsSolid()) { DataQuad(data, cube.Face[3]); }
			if (!nextY.IsSolid()) { DataQuad(data, cube.Face[4]); }
			if (!nextZ.IsSolid()) { DataQuad(data, cube.Face[5]); }
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
		temp.Pos.X = Index.X * CHUNK_VALUES_PER_SIDE * CHUNK_SCALE;
		temp.Pos.Y = Index.Y * CHUNK_VALUES_PER_SIDE * CHUNK_SCALE;
		temp.Pos.Z = Index.Z * CHUNK_VALUES_PER_SIDE * CHUNK_SCALE;
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
