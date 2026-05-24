#include "Perlin2D.hpp"
#include "Random.hpp"

#include "ValueType/Vector/I2.hpp"
#include "ValueType/LoopU2.hpp"
#include "ValueType/Angle.hpp"



Perlin2D::~Perlin2D()
{ }
Perlin2D::Perlin2D()
	: Nodes()
{ }
Perlin2D::Perlin2D(const Perlin2D & other)
	: Nodes(other.Nodes)
{ }
Perlin2D & Perlin2D::operator=(const Perlin2D & other)
{
	Nodes = other.Nodes;
	return *this;
}

Perlin2D::Perlin2D(VectorU2 count)
	: Nodes(count)
{ }

Perlin2D Perlin2D::Random(VectorU2 count)
{
	Perlin2D perlin(count);
	unsigned int c = perlin.Nodes.Length();
	for (unsigned int i = 0; i < c; i++)
	{
		Angle a = Angle::Degrees(Random::Float01In() * 360.0f);
		perlin.Nodes[i] = a.forward(VectorF2(0, 1));
	}
	return perlin;
}

VectorU2 Perlin2D::Normalize(VectorF2 node) const
{
	VectorU2 count = Nodes.Size();
	int x = node.X;
	int y = node.Y;
	while (x < 0) { x += count.X; }
	while (y < 0) { y += count.Y; }
	while (x >= (int)count.X) { x -= count.X; }
	while (y >= (int)count.Y) { y -= count.Y; }
	return VectorU2(x, y);
}

static float interpolate(float val0, float val1, float t)
{
	return (val0 * (1.0f - t)) + (val1 * (t - 0.0f));
}

float Perlin2D::Calculate(VectorF2 pos) const
{
	VectorF2 posF = pos.roundF();
	VectorI2 posI = posF;

	VectorF2 rel = pos - posI;
	VectorF2 rel0 = rel;
	VectorF2 rel1 = rel - VectorF2(1.0f);

	VectorU2 count = Nodes.Size();
	VectorU2 i0 = ((posI % count) + count) % count;
	VectorU2 i1 = (i0 + 1u) % count;

	i0.Y = i0.Y * count.X;
	i1.Y = i1.Y * count.X;

	float dotY[4] = {
		VectorF2::dot(Nodes[i0.X + i0.Y], VectorF2(rel0.X, rel0.Y)),
		VectorF2::dot(Nodes[i1.X + i0.Y], VectorF2(rel1.X, rel0.Y)),
		VectorF2::dot(Nodes[i0.X + i1.Y], VectorF2(rel0.X, rel1.Y)),
		VectorF2::dot(Nodes[i1.X + i1.Y], VectorF2(rel1.X, rel1.Y)),
	};

	float dotX[2] = {
		interpolate(dotY[0b00], dotY[0b10], rel.Y),
		interpolate(dotY[0b01], dotY[0b11], rel.Y),
	};

	return interpolate(dotX[0b0], dotX[0b1], rel.X);

	/*return interpolate(
		interpolate(
			VectorF2::dot(Nodes[i0.X + i0.Y], VectorF2(rel0.X, rel0.Y)),
			VectorF2::dot(Nodes[i0.X + i1.Y], VectorF2(rel0.X, rel1.Y)),
			rel.Y),
		interpolate(
			VectorF2::dot(Nodes[i1.X + i0.Y], VectorF2(rel1.X, rel0.Y)),
			VectorF2::dot(Nodes[i1.X + i1.Y], VectorF2(rel1.X, rel1.Y)),
			rel.Y),
		rel.X);*/
}
