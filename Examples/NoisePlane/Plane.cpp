#include "Plane.hpp"
#include "Perlin2D.hpp"



Plane::~Plane() { }

Plane::Plane()
{
	for (unsigned int i = 0; i < PLANE_CELL_PER_AREA; i++)
	{
		Heights[i] = 0.0f;
	}
}



Point2D Plane::Pos2At(Undex2D u) const
{
	return Point2D(
		((Pos.X * (PLANE_CELL_PER_SIDE)) + u.X) * PLANE_SCALE,
		((Pos.Y * (PLANE_CELL_PER_SIDE)) + u.Y) * PLANE_SCALE
	);
}
Point3D Plane::Pos3At(Undex2D u) const
{
	return Point3D(
		((Pos.X * (PLANE_CELL_PER_SIDE)) + u.X) * PLANE_SCALE,
		Heights[u.X + (u.Y * PLANE_CELL_PER_SIDE)],
		((Pos.Y * (PLANE_CELL_PER_SIDE)) + u.Y) * PLANE_SCALE
	);
}



void Plane::Generate(const Perlin2D & noise)
{
	for (unsigned int i = 0; i < PLANE_CELL_PER_AREA; i++)
	{
		Undex2D u(i % PLANE_CELL_PER_SIDE, i / PLANE_CELL_PER_SIDE);
		Point2D p = Pos2At(u);
		float val = 0.0f;
		val += noise.Calculate(p * 1) / 1;
		val += noise.Calculate(p * 2) / 2;
		val += noise.Calculate(p * 4) / 4;
		val += noise.Calculate(p * 8) / 8;
		Heights[i] = val;
	}
}
