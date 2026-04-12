#include "Chunk.hpp"
#include "Noise/Perlin2D.hpp"

#include "ValueType/Bool3.hpp"
#include "ValueType/VectorU3.hpp"

#include "ValueType/Undex2D.hpp"
#include "ValueType/UndexLoop2D.hpp"

#include "ValueType/Undex3D.hpp"
#include "ValueType/UndexLoop3D.hpp"

#include "Miscellaneous/Container/Binary.hpp"



Chunk::~Chunk() { }
Chunk::Chunk()
	: Values()
	, Index()
	, IsGenerated(false)
	, MainCount(0)
	, Buffer()
	, GraphicsExist(false)
	, BufferNeedsInit(false)
	, MainBufferNeedsData(false)
	, InstBufferNeedsData(false)
{
	for (unsigned int i = 0; i < CHUNK_VALUES_PER_VOLM; i++)
	{
		Values[i] = 0.0f;
	}
}



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
				Values[size3.Convert(u3)] = 0;
			}
			else
			{
				Values[size3.Convert(u3)] = 1;
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



static ColorF4 UndexToColor(Undex3D u)
{
	ColorF4 col;
	col.R = (u.X % 2);
	col.G = (u.Y % 2);
	col.B = (u.Z % 2);
	return col;
}

void Chunk::UpdateMainBuffer()
{
	if (!GraphicsExist) { return; }
	if (!MainBufferNeedsData) { return; }

	{
		Container::Binary<ChunkGraphics::MainData> data;

		// if voxel now empty. show 1 face to test for now
		Undex3D size(CHUNK_VALUES_PER_SIDE);
		Undex3D edge(CHUNK_VALUES_PER_SIDE - 1);
		UndexLoop3D loop(Undex3D(), edge);
		for (Undex3D u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
		{
			Undex3D u0 = Undex3D(u.X + 0, u.Y + 0, u.Z + 0);
			Undex3D u1 = Undex3D(u.X + 1, u.Y + 1, u.Z + 1);

			ChunkGraphics::MainData temp[8];
			temp[0b000].Pos = Point3D(u0.X, u0.Y, u0.Z) * CHUNK_SCALE;
			temp[0b001].Pos = Point3D(u1.X, u0.Y, u0.Z) * CHUNK_SCALE;
			temp[0b010].Pos = Point3D(u0.X, u1.Y, u0.Z) * CHUNK_SCALE;
			temp[0b011].Pos = Point3D(u1.X, u1.Y, u0.Z) * CHUNK_SCALE;
			temp[0b100].Pos = Point3D(u0.X, u0.Y, u1.Z) * CHUNK_SCALE;
			temp[0b101].Pos = Point3D(u1.X, u0.Y, u1.Z) * CHUNK_SCALE;
			temp[0b110].Pos = Point3D(u0.X, u1.Y, u1.Z) * CHUNK_SCALE;
			temp[0b111].Pos = Point3D(u1.X, u1.Y, u1.Z) * CHUNK_SCALE;

			ColorF4 col = UndexToColor(u);
			for (unsigned int i = 0; i < 8; i++) { temp[i].Col = col; }

			u0 = u0 % size;
			u1 = u1 % size;

			if (Values[size.Convert(u)] != 0)
			{
				if ((u.X != 0) && (Values[size.Convert(Undex3D(u.X - 1, u.Y, u.Z))] == 0))
				{
					data.Insert(temp[0b000]); data.Insert(temp[0b100]); data.Insert(temp[0b010]);
					data.Insert(temp[0b010]); data.Insert(temp[0b100]); data.Insert(temp[0b110]);
				}
				if ((u.Y != 0) && (Values[size.Convert(Undex3D(u.X, u.Y - 1, u.Z))] == 0))
				{
					data.Insert(temp[0b000]); data.Insert(temp[0b001]); data.Insert(temp[0b100]);
					data.Insert(temp[0b100]); data.Insert(temp[0b001]); data.Insert(temp[0b101]);
				}
				if ((u.Z != 0) && (Values[size.Convert(Undex3D(u.X, u.Y, u.Z - 1))] == 0))
				{
					data.Insert(temp[0b000]); data.Insert(temp[0b010]); data.Insert(temp[0b001]);
					data.Insert(temp[0b001]); data.Insert(temp[0b010]); data.Insert(temp[0b011]);
				}

				if ((u.X != CHUNK_VALUES_PER_SIDE - 1) && (Values[size.Convert(Undex3D(u.X + 1, u.Y, u.Z))] == 0))
				{
					data.Insert(temp[0b001]); data.Insert(temp[0b011]); data.Insert(temp[0b101]);
					data.Insert(temp[0b101]); data.Insert(temp[0b011]); data.Insert(temp[0b111]);
				}
				if ((u.Y != CHUNK_VALUES_PER_SIDE - 1) && (Values[size.Convert(Undex3D(u.X, u.Y + 1, u.Z))] == 0))
				{
					data.Insert(temp[0b010]); data.Insert(temp[0b110]); data.Insert(temp[0b011]);
					data.Insert(temp[0b011]); data.Insert(temp[0b110]); data.Insert(temp[0b111]);
				}
				if ((u.Z != CHUNK_VALUES_PER_SIDE - 1) && (Values[size.Convert(Undex3D(u.X, u.Y, u.Z + 1))] == 0))
				{
					data.Insert(temp[0b100]); data.Insert(temp[0b101]); data.Insert(temp[0b110]);
					data.Insert(temp[0b110]); data.Insert(temp[0b101]); data.Insert(temp[0b111]);
				}
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
		Container::Binary<ChunkGraphics::InstData> data;

		ChunkGraphics::InstData temp;
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
