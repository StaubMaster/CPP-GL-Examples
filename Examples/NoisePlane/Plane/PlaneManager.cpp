#include "PlaneManager.hpp"

#include "ValueType/Bool2D.hpp"
#include "ValueType/BoxI2.hpp"
#include "ValueType/LoopI2.hpp"

#include "ValueType/UndexBox2D.hpp"
#include "ValueType/UndexLoop2D.hpp"



PlaneManager::~PlaneManager() { }
PlaneManager::PlaneManager()
	: Shader()
	, Planes()
	, ShouldGenerate(true)
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
unsigned int PlaneManager::FindPlaneUndex(VectorI2 idx) const
{
	for (unsigned int i = 0; i < Planes.Count(); i++)
	{
		if (((*Planes[i]).Index == idx).All(true))
		{
			return i;
		}
	}
	return 0xFFFFFFFF;
}
Plane * PlaneManager::FindPlaneOrNull(VectorI2 idx) const
{
	for (unsigned int i = 0; i < Planes.Count(); i++)
	{
		if (((*Planes[i]).Index == idx).All(true))
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
	Point2D r = (pos / (PLANE_VALUES_PER_SIDE * PLANE_SCALE)).roundF();
	VectorI2 idx(r);

	unsigned int size = 5;
	BoxI2 box(idx - VectorI2(size), idx + VectorI2(size));

	LoopI2 loop(box.Min, box.Max);
	for (VectorI2 i = loop.Min(); loop.Check(i).All(true); loop.Next(i))
	{
		Generate(noise, i);
	}
}

void PlaneManager::Generate(const Perlin2D & noise, VectorI2 idx)
{
	if (!ShouldGenerate) { return; }

	Plane * plane = FindPlaneOrNull(idx);
	if (plane == nullptr)
	{
		plane = new Plane();
		plane -> Index = idx;
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
	PlaneNeighbours & neighbours = plane.Neighbours;
	{
		neighbours.Planes[0b00] = FindPlaneOrNull(VectorI2(plane.Index.X + 0, plane.Index.Y + 0));
		neighbours.Planes[0b01] = FindPlaneOrNull(VectorI2(plane.Index.X + 1, plane.Index.Y + 0));
		neighbours.Planes[0b10] = FindPlaneOrNull(VectorI2(plane.Index.X + 0, plane.Index.Y + 1));
		neighbours.Planes[0b11] = FindPlaneOrNull(VectorI2(plane.Index.X + 1, plane.Index.Y + 1));
	}
	{
		Plane * planes[4];

		planes[0b00] = FindPlaneOrNull(VectorI2(plane.Index.X - 0, plane.Index.Y - 0));
		planes[0b01] = FindPlaneOrNull(VectorI2(plane.Index.X - 1, plane.Index.Y - 0));
		planes[0b10] = FindPlaneOrNull(VectorI2(plane.Index.X - 0, plane.Index.Y - 1));
		planes[0b11] = FindPlaneOrNull(VectorI2(plane.Index.X - 1, plane.Index.Y - 1));

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
