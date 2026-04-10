#include "Plane.hpp"
#include "Perlin2D.hpp"

#include "ValueType/Bool2D.hpp"
#include "Miscellaneous/Container/Binary.hpp"



Plane::~Plane() { }

Plane::Plane()
	: Values()
	, Undex()
	, IsGenerated(false)
	, Buffer()
	, GraphicsExist(false)
	, BufferNeedsInit(false)
	, MainBufferNeedsData(false)
	, InstBufferNeedsData(false)
{
	for (unsigned int i = 0; i < PLANE_VALUES_PER_AREA; i++)
	{
		Values[i] = 0.0f;
	}
}



void Plane::Generate(const Perlin2D & noise)
{
	if (IsGenerated) { return; }

	Undex2D size(PLANE_VALUES_PER_SIDE, PLANE_VALUES_PER_SIDE);
	Point2D pos = Point2D(Undex.X, Undex.Y) * PLANE_VALUES_PER_SIDE;
	for (unsigned int i = 0; i < PLANE_VALUES_PER_AREA; i++)
	{
		Undex2D u = size.ConvertX(i);
		Point2D p(
			(pos.X + u.X) * PLANE_SCALE,
			(pos.Y + u.Y) * PLANE_SCALE
		);
		float val = 0.0f;
		val += noise.Calculate(p * 1) / 1;
		val += noise.Calculate(p * 2) / 2;
		val += noise.Calculate(p * 4) / 4;
		val += noise.Calculate(p * 8) / 8;
		Values[i] = val;
	}

	IsGenerated = true;

	if (GraphicsExist)
	{
		MainBufferNeedsData = true;
	}
}



void Plane::GraphicsCreate()
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
void Plane::GraphicsDelete()
{
	if (!GraphicsExist) { return; }

	Buffer.Delete();

	GraphicsExist = false;
}



void Plane::UpdateMainBuffer()
{
	if (!GraphicsExist) { return; }
	if (!MainBufferNeedsData) { return; }

	{
		Container::Binary<PlaneGraphics::MainData> data;
		Undex2D size(PLANE_VALUES_PER_SIDE, PLANE_VALUES_PER_SIDE);
		for (unsigned int i = 0; i < PLANE_VALUES_PER_AREA; i++)
		{
			Undex2D u = size.ConvertX(i);
			Undex2D u0 = Undex2D(u.X + 0, u.Y + 0) % size;
			Undex2D u1 = Undex2D(u.X + 1, u.Y + 1) % size;
			Bool2D comp = u0 < u1;

			unsigned int udxs[4];
			udxs[0b00] = size.ConvertX(Undex2D(u0.X, u0.Y));
			udxs[0b01] = size.ConvertX(Undex2D(u1.X, u0.Y));
			udxs[0b10] = size.ConvertX(Undex2D(u0.X, u1.Y));
			udxs[0b11] = size.ConvertX(Undex2D(u1.X, u1.Y));

			PlaneValue vals[4];

			if (comp.GetX() && comp.GetY())
			{
				vals[0b00] = Neighbours.Value(0b00, udxs[0b00]);
				vals[0b01] = Neighbours.Value(0b00, udxs[0b01]);
				vals[0b10] = Neighbours.Value(0b00, udxs[0b10]);
				vals[0b11] = Neighbours.Value(0b00, udxs[0b11]);
			}

			if (!comp.GetX() && comp.GetY())
			{
				vals[0b00] = Neighbours.Value(0b00, udxs[0b00]);
				vals[0b01] = Neighbours.Value(0b01, udxs[0b01]);
				vals[0b10] = Neighbours.Value(0b00, udxs[0b10]);
				vals[0b11] = Neighbours.Value(0b01, udxs[0b11]);
			}

			if (comp.GetX() && !comp.GetY())
			{
				vals[0b00] = Neighbours.Value(0b00, udxs[0b00]);
				vals[0b01] = Neighbours.Value(0b00, udxs[0b01]);
				vals[0b10] = Neighbours.Value(0b10, udxs[0b10]);
				vals[0b11] = Neighbours.Value(0b10, udxs[0b11]);
			}

			if (!comp.GetX() && !comp.GetY())
			{
				vals[0b00] = Neighbours.Value(0b00, udxs[0b00]);
				vals[0b01] = Neighbours.Value(0b01, udxs[0b01]);
				vals[0b10] = Neighbours.Value(0b10, udxs[0b10]);
				vals[0b11] = Neighbours.Value(0b11, udxs[0b11]);
			}

			PlaneGraphics::MainData temp[4];

			temp[0b00].Pos = Point3D((u.X + 0) * PLANE_SCALE, vals[0b00].Value, (u.Y + 0) * PLANE_SCALE);
			temp[0b01].Pos = Point3D((u.X + 1) * PLANE_SCALE, vals[0b01].Value, (u.Y + 0) * PLANE_SCALE);
			temp[0b10].Pos = Point3D((u.X + 0) * PLANE_SCALE, vals[0b10].Value, (u.Y + 1) * PLANE_SCALE);
			temp[0b11].Pos = Point3D((u.X + 1) * PLANE_SCALE, vals[0b11].Value, (u.Y + 1) * PLANE_SCALE);

			temp[0b00].Col = vals[0b00].ToColor();
			temp[0b01].Col = vals[0b01].ToColor();
			temp[0b10].Col = vals[0b10].ToColor();
			temp[0b11].Col = vals[0b11].ToColor();

			if (vals[0b00].Known && vals[0b01].Known && vals[0b10].Known) { data.Insert(temp[0b00]); data.Insert(temp[0b10]); data.Insert(temp[0b01]); }
			if (vals[0b10].Known && vals[0b01].Known && vals[0b11].Known) { data.Insert(temp[0b01]); data.Insert(temp[0b10]); data.Insert(temp[0b11]); }
		}
		Buffer.Main.Change(data);
	}

	MainBufferNeedsData = false;
}
void Plane::UpdateInstBuffer()
{
	if (!GraphicsExist) { return; }
	if (!InstBufferNeedsData) { return; }

	{
		Container::Binary<PlaneGraphics::InstData> data;
		
		PlaneGraphics::InstData temp;
		temp.Pos.X = Undex.X * PLANE_VALUES_PER_SIDE * PLANE_SCALE;
		temp.Pos.Y = 0;
		temp.Pos.Z = Undex.Y * PLANE_VALUES_PER_SIDE * PLANE_SCALE;
		data.Insert(temp);
		
		Buffer.Inst.Change(data);
	}

	InstBufferNeedsData = false;
}



void Plane::Draw()
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
