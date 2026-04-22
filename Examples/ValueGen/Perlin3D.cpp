#include "Perlin3D.hpp"
#include "Random.hpp"

#include "ValueType/VectorI3.hpp"
#include "ValueType/UndexLoop3D.hpp"
#include "ValueType/EulerAngle3D.hpp"



Perlin3D::~Perlin3D()
{
	delete[] Data;
}
Perlin3D::Perlin3D()
	: Count(0, 0, 0)
	, Data(nullptr)
{ }
Perlin3D::Perlin3D(const Perlin3D & other)
	: Count(other.Count)
	, Data(new VectorF3[Count.Product()])
{
	unsigned int c = Count.Product();
	for (unsigned int i = 0; i < c; i++)
	{
		Data[i] = other.Data[i];
	}
}
Perlin3D & Perlin3D::operator=(const Perlin3D & other)
{
	delete[] Data;
	Count = other.Count;
	Data = new VectorF3[Count.Product()];

	unsigned int c = Count.Product();
	for (unsigned int i = 0; i < c; i++)
	{
		Data[i] = other.Data[i];
	}

	return *this;
}

Perlin3D::Perlin3D(VectorU3 count)
	: Count(count)
	, Data(new VectorF3[Count.Product()])
{ }

Perlin3D Perlin3D::Random(VectorU3 count)
{
	Perlin3D perlin(count);
	unsigned int c = perlin.Count.Product();
	for (unsigned int i = 0; i < c; i++)
	{
		EulerAngle3D a = EulerAngle3D::Degrees(
			Random::Float01In() * 360.0f,
			Random::Float01In() * 360.0f,
			Random::Float01In() * 360.0f
		);
		perlin.Data[i] = a.forward(VectorF3(0, 0, 1));
	}
	return perlin;
}

VectorU3 Perlin3D::Normalize(VectorF3 node) const
{
	int x = node.X;
	int y = node.Y;
	int z = node.Z;
	while (x < 0) { x += Count.X; }
	while (y < 0) { y += Count.Y; }
	while (z < 0) { z += Count.Z; }
	while (x >= (int)Count.X) { x -= Count.X; }
	while (y >= (int)Count.Y) { y -= Count.Y; }
	while (z >= (int)Count.Z) { z -= Count.Z; }
	return VectorU3(x, y, z);
}

static float lerp(float val0, float val1, float t)
{
	return (val0 * (1.0f - t)) + (val1 * (t - 0.0f));
}



float Perlin3D::Calculate(VectorF3 pos) const
{
	VectorF3 posF = pos.roundF();
	VectorI3 posI = posF;
	VectorF3 rel = pos - posI;

	VectorU3 i0 = ((posI % Count) + Count) % Count;
	VectorU3 i1 = (i0 + VectorU3(1)) % Count;

	VectorF3 dirs[8];
	dirs[0b000] = Data[Count.Convert(VectorU3(i0.X, i0.Y, i0.Z))];
	dirs[0b001] = Data[Count.Convert(VectorU3(i1.X, i0.Y, i0.Z))];
	dirs[0b010] = Data[Count.Convert(VectorU3(i0.X, i1.Y, i0.Z))];
	dirs[0b011] = Data[Count.Convert(VectorU3(i1.X, i1.Y, i0.Z))];

	dirs[0b100] = Data[Count.Convert(VectorU3(i0.X, i0.Y, i1.Z))];
	dirs[0b101] = Data[Count.Convert(VectorU3(i1.X, i0.Y, i1.Z))];
	dirs[0b110] = Data[Count.Convert(VectorU3(i0.X, i1.Y, i1.Z))];
	dirs[0b111] = Data[Count.Convert(VectorU3(i1.X, i1.Y, i1.Z))];

	VectorF3 rels[8];
	rels[0b000] = VectorF3(rel.X - 0, rel.Y - 0, rel.Z - 0);
	rels[0b001] = VectorF3(rel.X - 1, rel.Y - 0, rel.Z - 0);
	rels[0b010] = VectorF3(rel.X - 0, rel.Y - 1, rel.Z - 0);
	rels[0b011] = VectorF3(rel.X - 1, rel.Y - 1, rel.Z - 0);

	rels[0b100] = VectorF3(rel.X - 0, rel.Y - 0, rel.Z - 1);
	rels[0b101] = VectorF3(rel.X - 1, rel.Y - 0, rel.Z - 1);
	rels[0b110] = VectorF3(rel.X - 0, rel.Y - 1, rel.Z - 1);
	rels[0b111] = VectorF3(rel.X - 1, rel.Y - 1, rel.Z - 1);

	float dots[8];
	dots[0b000] = VectorF3::dot(dirs[0b000], rels[0b000]);
	dots[0b001] = VectorF3::dot(dirs[0b001], rels[0b001]);
	dots[0b010] = VectorF3::dot(dirs[0b010], rels[0b010]);
	dots[0b011] = VectorF3::dot(dirs[0b011], rels[0b011]);

	dots[0b100] = VectorF3::dot(dirs[0b100], rels[0b100]);
	dots[0b101] = VectorF3::dot(dirs[0b101], rels[0b101]);
	dots[0b110] = VectorF3::dot(dirs[0b110], rels[0b110]);
	dots[0b111] = VectorF3::dot(dirs[0b111], rels[0b111]);

	float dot_00 = lerp(dots[0b000], dots[0b100], rel.Z);
	float dot_01 = lerp(dots[0b001], dots[0b101], rel.Z);
	float dot_10 = lerp(dots[0b010], dots[0b110], rel.Z);
	float dot_11 = lerp(dots[0b011], dots[0b111], rel.Z);

	float dot__0 = lerp(dot_00, dot_10, rel.Y);
	float dot__1 = lerp(dot_01, dot_11, rel.Y);

	float dot___ = lerp(dot__0, dot__1, rel.X);

	return dot___;
}
