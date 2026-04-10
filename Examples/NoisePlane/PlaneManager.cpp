#include "PlaneManager.hpp"

#include "ValueType/Bool2D.hpp"



PlaneManager::~PlaneManager() { }
PlaneManager::PlaneManager()
{ }

void PlaneManager::GenerateAround(const Perlin2D & noise, Point2D pos)
{
	(void)pos;
	Undex2D size(PLANES_PER_SIDE, PLANES_PER_SIDE);
	for (unsigned int i = 0; i < PLANES_PER_AREA; i++)
	{
		Undex2D u = size.ConvertX(i);
		Planes[i].Undex = u;
		Planes[i].Generate(noise);
	}
}

void PlaneManager::PlanesToBuffers()
{
	for (unsigned int i = 0; i < PLANES_PER_AREA; i++)
	{
		UpdateNeighboursAround(Planes[i]);
	}
}

void PlaneManager::UpdateNeighboursAround(Plane & plane)
{
	Undex2D size(PLANES_PER_SIDE, PLANES_PER_SIDE);
	Bool2D comp(plane.Undex != Undex2D(PLANES_PER_SIDE - 1, PLANES_PER_SIDE - 1));

	unsigned int udxs[4];
	udxs[0b00] = size.ConvertX(Undex2D(plane.Undex.X + 0, plane.Undex.Y + 0));
	udxs[0b01] = size.ConvertX(Undex2D(plane.Undex.X + 1, plane.Undex.Y + 0));
	udxs[0b10] = size.ConvertX(Undex2D(plane.Undex.X + 0, plane.Undex.Y + 1));
	udxs[0b11] = size.ConvertX(Undex2D(plane.Undex.X + 1, plane.Undex.Y + 1));

									{ plane.Neighbours.Planes[0b00] = &Planes[udxs[0b00]]; }
	if (comp.GetX())				{ plane.Neighbours.Planes[0b01] = &Planes[udxs[0b01]]; }
	if (comp.GetY())				{ plane.Neighbours.Planes[0b10] = &Planes[udxs[0b10]]; }
	if (comp.GetX() && comp.GetY())	{ plane.Neighbours.Planes[0b11] = &Planes[udxs[0b10]]; }
}



void PlaneManager::GraphicsCreate()
{
	Shader.Create();
	for (unsigned int i = 0; i < PLANES_PER_AREA; i++)
	{
		Planes[i].GraphicsCreate();
	}
}
void PlaneManager::GraphicsDelete()
{
	Shader.Delete();
	for (unsigned int i = 0; i < PLANES_PER_AREA; i++)
	{
		Planes[i].GraphicsDelete();
	}
}
void PlaneManager::Draw()
{
	Shader.Bind();
	for (unsigned int i = 0; i < PLANES_PER_AREA; i++)
	{
		Planes[i].Draw();
	}
}
