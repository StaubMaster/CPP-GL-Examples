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



void Plane::Generate(const Perlin2D & noise)
{
	Undex2D size(PLANE_CELL_PER_SIDE, PLANE_CELL_PER_SIDE);
	Point2D pos = Pos * PLANE_CELL_PER_SIDE;
	for (unsigned int i = 0; i < PLANE_CELL_PER_AREA; i++)
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
		Heights[i] = val;
	}
}
