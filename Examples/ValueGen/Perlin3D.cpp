#include "Perlin3D.hpp"
#include "Random.hpp"

#include "ValueType/Vector/I3.hpp"
#include "ValueType/LoopU3.hpp"
#include "ValueType/EulerAngle3D.hpp"



Perlin3D::~Perlin3D()
{ }
Perlin3D::Perlin3D()
	: Nodes()
{ }
Perlin3D::Perlin3D(const Perlin3D & other)
	: Nodes(other.Nodes)
{ }
Perlin3D & Perlin3D::operator=(const Perlin3D & other)
{
	Nodes = other.Nodes;
	return *this;
}

Perlin3D::Perlin3D(VectorU3 count)
	: Nodes(count)
{ }

Perlin3D Perlin3D::Random(VectorU3 count)
{
	Perlin3D perlin(count);
	unsigned int c = perlin.Nodes.Length();
	for (unsigned int i = 0; i < c; i++)
	{
		EulerAngle3D a = EulerAngle3D::Degrees(
			Random::Float01In() * 360.0f,
			Random::Float01In() * 360.0f,
			Random::Float01In() * 360.0f
		);
		perlin.Nodes[i] = a.forward(VectorF3(0, 0, 1));
	}
	return perlin;
}

VectorU3 Perlin3D::Normalize(VectorF3 node) const
{
	VectorU3 count = Nodes.Size();
	int x = node.X;
	int y = node.Y;
	int z = node.Z;
	while (x < 0) { x += count.X; }
	while (y < 0) { y += count.Y; }
	while (z < 0) { z += count.Z; }
	while (x >= (int)count.X) { x -= count.X; }
	while (y >= (int)count.Y) { y -= count.Y; }
	while (z >= (int)count.Z) { z -= count.Z; }
	return VectorU3(x, y, z);
}

static float interpolate(float val0, float val1, float t)
{
	//t = (3.0f - t * 2.0f) * t * t;
	return (val0 * (1.0f - t)) + (val1 * (t - 0.0f));
}



float Perlin3D::Calculate(VectorF3 pos) const
{
	VectorF3 posF = pos.roundF();
	VectorI3 posI = posF;

	VectorF3 rel = pos - posI;
	VectorF3 rel0 = rel;
	VectorF3 rel1 = rel - VectorF3(1.0f);

	VectorU3 count = Nodes.Size();
	VectorU3 i0 = ((posI % count) + count) % count;
	VectorU3 i1 = (i0 + VectorU3(1)) % count; // do this with if checks ?

	i0.Y = i0.Y * count.X; i0.Z = i0.Z * count.X * count.Y;
	i1.Y = i1.Y * count.X; i1.Z = i1.Z * count.X * count.Y;

	float dotZ[8] ={
		VectorF3::dot(Nodes[i0.X + i0.Y + i0.Z], VectorF3(rel0.X, rel0.Y, rel0.Z)),
		VectorF3::dot(Nodes[i1.X + i0.Y + i0.Z], VectorF3(rel1.X, rel0.Y, rel0.Z)),
		VectorF3::dot(Nodes[i0.X + i1.Y + i0.Z], VectorF3(rel0.X, rel1.Y, rel0.Z)),
		VectorF3::dot(Nodes[i1.X + i1.Y + i0.Z], VectorF3(rel1.X, rel1.Y, rel0.Z)),
		VectorF3::dot(Nodes[i0.X + i0.Y + i1.Z], VectorF3(rel0.X, rel0.Y, rel1.Z)),
		VectorF3::dot(Nodes[i1.X + i0.Y + i1.Z], VectorF3(rel1.X, rel0.Y, rel1.Z)),
		VectorF3::dot(Nodes[i0.X + i1.Y + i1.Z], VectorF3(rel0.X, rel1.Y, rel1.Z)),
		VectorF3::dot(Nodes[i1.X + i1.Y + i1.Z], VectorF3(rel1.X, rel1.Y, rel1.Z)),
	};

	float dotY[4] = {
		interpolate(dotZ[0b000], dotZ[0b100], rel.Z),
		interpolate(dotZ[0b001], dotZ[0b101], rel.Z),
		interpolate(dotZ[0b010], dotZ[0b110], rel.Z),
		interpolate(dotZ[0b011], dotZ[0b111], rel.Z),
	};

	float dotX[2] = {
		interpolate(dotY[0b00], dotY[0b10], rel.Y),
		interpolate(dotY[0b01], dotY[0b11], rel.Y),
	};

	return interpolate(dotX[0b0], dotX[0b1], rel.X);

	/*return interpolate(
		interpolate(
			interpolate(
				VectorF3::dot(Nodes[i0.X + i0.Y + i0.Z], VectorF3(rel0.X, rel0.Y, rel0.Z)),
				VectorF3::dot(Nodes[i0.X + i0.Y + i1.Z], VectorF3(rel0.X, rel0.Y, rel1.Z)),
				rel.Z),
			interpolate(
				VectorF3::dot(Nodes[i0.X + i1.Y + i0.Z], VectorF3(rel0.X, rel1.Y, rel0.Z)),
				VectorF3::dot(Nodes[i0.X + i1.Y + i1.Z], VectorF3(rel0.X, rel1.Y, rel1.Z)),
				rel.Z),
			rel.Y),
		interpolate(
			interpolate(
				VectorF3::dot(Nodes[i1.X + i0.Y + i0.Z], VectorF3(rel1.X, rel0.Y, rel0.Z)),
				VectorF3::dot(Nodes[i1.X + i0.Y + i1.Z], VectorF3(rel1.X, rel0.Y, rel1.Z)),
				rel.Z),
			interpolate(
				VectorF3::dot(Nodes[i1.X + i1.Y + i0.Z], VectorF3(rel1.X, rel1.Y, rel0.Z)),
				VectorF3::dot(Nodes[i1.X + i1.Y + i1.Z], VectorF3(rel1.X, rel1.Y, rel1.Z)),
				rel.Z),
			rel.Y),
		rel.X);*/
}
