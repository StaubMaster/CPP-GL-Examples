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
	if (((u.X % 2) == (u.Z % 2)) == ((u.Y % 2) == 0))
	{
		col = ColorF4(0.75f, 0.75f, 0.75f);
	}
	else
	{
		col = ColorF4(0.25f, 0.25f, 0.25f);
	}
	return col;
}

#include <iostream>
#include "ValueType/_Show.hpp"
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

				//{ data.Insert(temp[0b000]); data.Insert(temp[0b010]); data.Insert(temp[0b001]); }
				//{ data.Insert(temp[0b001]); data.Insert(temp[0b010]); data.Insert(temp[0b011]); }
				//{ data.Insert(temp[0b100]); data.Insert(temp[0b101]); data.Insert(temp[0b110]); }
				//{ data.Insert(temp[0b110]); data.Insert(temp[0b101]); data.Insert(temp[0b111]); }
			}
		}

		std::cout << "count " << data.Count() << '\n';
		/*for (unsigned int i = 0; i < data.Count(); i++)
		{
			std::cout << data[i].Pos << '\n';
		}*/
		std::cout << '\n';

		/*Undex2D size(CHUNK_VALUES_PER_SIDE, CHUNK_VALUES_PER_SIDE);
		UndexLoop2D loop(Undex2D(), size);
		for (Undex2D u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
		{
			Undex2D u0 = Undex2D(u.X + 0, u.Y + 0) % size;
			Undex2D u1 = Undex2D(u.X + 1, u.Y + 1) % size;
			Bool2D comp = u0 < u1;

			unsigned int udxs[4];
			udxs[0b00] = size.Convert(Undex2D(u0.X, u0.Y));
			udxs[0b01] = size.Convert(Undex2D(u1.X, u0.Y));
			udxs[0b10] = size.Convert(Undex2D(u0.X, u1.Y));
			udxs[0b11] = size.Convert(Undex2D(u1.X, u1.Y));

			ChunkValue vals[4];

			if (comp.GetX() && comp.GetY())
			{
				vals[0b00] = Neighbours.Value(0b00, udxs[0b00]);
				vals[0b01] = Neighbours.Value(0b00, udxs[0b01]);
				vals[0b10] = Neighbours.Value(0b00, udxs[0b10]);
				vals[0b11] = Neighbours.Value(0b00, udxs[0b11]);
			}

			ChunkGraphics::MainData temp[4];

			temp[0b00].Pos = Point3D((u.X + 0) * CHUNK_SCALE, vals[0b00].Value, (u.Y + 0) * CHUNK_SCALE);
			temp[0b01].Pos = Point3D((u.X + 1) * CHUNK_SCALE, vals[0b01].Value, (u.Y + 0) * CHUNK_SCALE);
			temp[0b10].Pos = Point3D((u.X + 0) * CHUNK_SCALE, vals[0b10].Value, (u.Y + 1) * CHUNK_SCALE);
			temp[0b11].Pos = Point3D((u.X + 1) * CHUNK_SCALE, vals[0b11].Value, (u.Y + 1) * CHUNK_SCALE);

			temp[0b00].Col = vals[0b00].ToColor();
			temp[0b01].Col = vals[0b01].ToColor();
			temp[0b10].Col = vals[0b10].ToColor();
			temp[0b11].Col = vals[0b11].ToColor();

			{
				float factor = 0.5f;
				if ((u.X % 2) == (u.Y % 2))
				{
					factor = factor - 0.125f;
				}
				else
				{
					factor = factor + 0.125f;
				}
				ColorF4 col(factor, factor, factor);
				temp[0b00].Col = col;
				temp[0b01].Col = col;
				temp[0b10].Col = col;
				temp[0b11].Col = col;
			}

			if (vals[0b00].Known && vals[0b01].Known && vals[0b10].Known) { data.Insert(temp[0b00]); data.Insert(temp[0b10]); data.Insert(temp[0b01]); }
			if (vals[0b10].Known && vals[0b01].Known && vals[0b11].Known) { data.Insert(temp[0b01]); data.Insert(temp[0b10]); data.Insert(temp[0b11]); }
		}*/

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
