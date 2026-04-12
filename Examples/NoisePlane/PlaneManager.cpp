#include "PlaneManager.hpp"

#include "ValueType/Bool2D.hpp"
#include "ValueType/UndexBox2D.hpp"
#include "ValueType/UndexLoop2D.hpp"



PlaneManager::~PlaneManager() { }
PlaneManager::PlaneManager()
	: Shader()
	, Planes()
	, GraphicsExist(false)
{ }



unsigned int PlaneManager::FindPlaneUndex(Plane * plane) const
{
	for (unsigned int i = 0; i < Planes.Count(); i++)
	{
		if (Planes[i] == plane)
		{
			return i;
		}
	}
	return 0xFFFFFFFF;
}
unsigned int PlaneManager::FindPlaneUndex(Undex2D udx) const
{
	for (unsigned int i = 0; i < Planes.Count(); i++)
	{
		if (((*Planes[i]).Undex == udx).All(true))
		{
			return i;
		}
	}
	return 0xFFFFFFFF;
}
Plane * PlaneManager::FindPlaneOrNull(Undex2D udx) const
{
	for (unsigned int i = 0; i < Planes.Count(); i++)
	{
		if (((*Planes[i]).Undex == udx).All(true))
		{
			return Planes[i];
		}
	}
	return nullptr;
}



void PlaneManager::Clear()
{
	for (unsigned int i = 0; i < Planes.Count(); i++)
	{
		delete Planes[i];
	}
	Planes.Clear();
}
void PlaneManager::UpdateAround(const Perlin2D & noise, Point2D pos)
{
	if (pos.X < 0 || pos.Y < 0) { return; }
	Point2D r = (pos / (PLANE_VALUES_PER_SIDE * PLANE_SCALE)).roundF();
	Undex2D udx(r.X, r.Y);

	unsigned int size = 5;
	UndexBox2D box(udx - Undex2D(size, size), udx + Undex2D(size, size));
	if (box.Min.X > box.Max.X) { box.Min.X = 0; }
	if (box.Min.Y > box.Max.Y) { box.Min.Y = 0; }

	UndexLoop2D loop(box.Min, box.Max);
	for (Undex2D u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		Generate(noise, u);
	}
}

void PlaneManager::Generate(const Perlin2D & noise, Undex2D udx)
{
	Plane * plane = FindPlaneOrNull(udx);
	if (plane == nullptr)
	{
		plane = new Plane();
		plane -> Undex = udx;
		plane -> Generate(noise);

		Planes.Insert(plane);
		NeighbourInsert(*plane);

		plane -> Buffer.Main.Pos.Change(0);
		plane -> Buffer.Main.Col.Change(1);
		plane -> Buffer.Inst.Pos.Change(2);
		if (GraphicsExist)
		{
			plane -> GraphicsCreate();
		}
	}
}

void PlaneManager::NeighbourInsert(Plane & plane)
{
	{
		Plane * planes[4];

		planes[0b00] = FindPlaneOrNull(Undex2D(plane.Undex.X + 0, plane.Undex.Y + 0));
		planes[0b01] = FindPlaneOrNull(Undex2D(plane.Undex.X + 1, plane.Undex.Y + 0));
		planes[0b10] = FindPlaneOrNull(Undex2D(plane.Undex.X + 0, plane.Undex.Y + 1));
		planes[0b11] = FindPlaneOrNull(Undex2D(plane.Undex.X + 1, plane.Undex.Y + 1));
		
		if (planes[0b00] != nullptr) { plane.Neighbours.Planes[0b00] = planes[0b00]; }
		if (planes[0b01] != nullptr) { plane.Neighbours.Planes[0b01] = planes[0b01]; }
		if (planes[0b10] != nullptr) { plane.Neighbours.Planes[0b10] = planes[0b10]; }
		if (planes[0b11] != nullptr) { plane.Neighbours.Planes[0b11] = planes[0b11]; }
	}
	{
		Plane * planes[4];

		planes[0b00] = FindPlaneOrNull(Undex2D(plane.Undex.X - 0, plane.Undex.Y - 0));
		planes[0b01] = FindPlaneOrNull(Undex2D(plane.Undex.X - 1, plane.Undex.Y - 0));
		planes[0b10] = FindPlaneOrNull(Undex2D(plane.Undex.X - 0, plane.Undex.Y - 1));
		planes[0b11] = FindPlaneOrNull(Undex2D(plane.Undex.X - 1, plane.Undex.Y - 1));

		if (planes[0b00] != nullptr) { planes[0b00] -> Neighbours.Planes[0b00] = &plane; }
		if (planes[0b01] != nullptr) { planes[0b01] -> Neighbours.Planes[0b01] = &plane; }
		if (planes[0b10] != nullptr) { planes[0b10] -> Neighbours.Planes[0b10] = &plane; }
		if (planes[0b11] != nullptr) { planes[0b11] -> Neighbours.Planes[0b11] = &plane; }

		if (planes[0b00] != nullptr) { planes[0b00] -> MainBufferNeedsData = true; }
		if (planes[0b01] != nullptr) { planes[0b01] -> MainBufferNeedsData = true; }
		if (planes[0b10] != nullptr) { planes[0b10] -> MainBufferNeedsData = true; }
		if (planes[0b11] != nullptr) { planes[0b11] -> MainBufferNeedsData = true; }
	}
}



void PlaneManager::GraphicsCreate()
{
	if (GraphicsExist) { return; }

	Shader.Create();
	for (unsigned int i = 0; i < Planes.Count(); i++)
	{
		(*Planes[i]).GraphicsCreate();
	}

	GraphicsExist = true;
}
void PlaneManager::GraphicsDelete()
{
	if (!GraphicsExist) { return; }

	Shader.Delete();
	for (unsigned int i = 0; i < Planes.Count(); i++)
	{
		(*Planes[i]).GraphicsDelete();
	}

	GraphicsExist = false;
}

void PlaneManager::Draw()
{
	if (!GraphicsExist) { return; }

	Shader.Bind();
	for (unsigned int i = 0; i < Planes.Count(); i++)
	{
		(*Planes[i]).Draw();
	}
}
