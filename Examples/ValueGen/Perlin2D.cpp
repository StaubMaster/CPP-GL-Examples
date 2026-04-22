#include "Perlin2D.hpp"
#include "Random.hpp"

#include "ValueType/VectorI2.hpp"
#include "ValueType/UndexLoop2D.hpp"
#include "ValueType/Angle.hpp"



Perlin2D::~Perlin2D()
{
	delete[] Data;
}
Perlin2D::Perlin2D()
	: Count(0, 0)
	, Data(nullptr)
{ }
Perlin2D::Perlin2D(const Perlin2D & other)
	: Count(other.Count)
	, Data(new VectorF2[Count.Product()])
{
	unsigned int c = Count.Product();
	for (unsigned int i = 0; i < c; i++)
	{
		Data[i] = other.Data[i];
	}
}
Perlin2D & Perlin2D::operator=(const Perlin2D & other)
{
	delete[] Data;
	Count = other.Count;
	Data = new VectorF2[Count.Product()];

	unsigned int c = Count.Product();
	for (unsigned int i = 0; i < c; i++)
	{
		Data[i] = other.Data[i];
	}

	return *this;
}

Perlin2D::Perlin2D(VectorU2 count)
	: Count(count)
	, Data(new VectorF2[Count.Product()])
{ }

Perlin2D Perlin2D::Random(VectorU2 count)
{
	Perlin2D perlin(count);
	unsigned int c = perlin.Count.Product();
	for (unsigned int i = 0; i < c; i++)
	{
		Angle a = Angle::Degrees(Random::Float01In() * 360.0f);
		perlin.Data[i] = a.forward(VectorF2(0, 1));
	}
	return perlin;
}

VectorU2 Perlin2D::Normalize(VectorF2 node) const
{
	int x = node.X;
	int y = node.Y;
	while (x < 0) { x += Count.X; }
	while (y < 0) { y += Count.Y; }
	while (x >= (int)Count.X) { x -= Count.X; }
	while (y >= (int)Count.Y) { y -= Count.Y; }
	return VectorU2(x, y);
}

static float lerp(float val0, float val1, float t)
{
	return (val0 * (1.0f - t)) + (val1 * (t - 0.0f));
}

#include <iostream>
#include "ValueType/_Show.hpp"

static bool DebugStatus = false;
void Perlin2D::DebugChange(bool status) { DebugStatus = status; }

#include "ValueType/AxisBox1D.hpp"
#include "ValueType/AxisBox2D.hpp"
static AxisBox2D debug_rel;
static AxisBox1D debug_rels[4];
static AxisBox1D debug_dots[4];
static AxisBox1D debug_dot0;
static AxisBox1D debug_dot1;
static AxisBox1D debug_dot;
void Perlin2D::DebugShow()
{
	std::cout << "rel " << debug_rel << '\n';

	//std::cout << "debug_rels[0b00] " << debug_rels[0b00] << '\n';
	//std::cout << "debug_rels[0b01] " << debug_rels[0b01] << '\n';
	//std::cout << "debug_rels[0b10] " << debug_rels[0b10] << '\n';
	//std::cout << "debug_rels[0b11] " << debug_rels[0b11] << '\n';

	std::cout << "dots[0b00] " << debug_dots[0b00] << '\n';
	std::cout << "dots[0b01] " << debug_dots[0b01] << '\n';
	std::cout << "dots[0b10] " << debug_dots[0b10] << '\n';
	std::cout << "dots[0b11] " << debug_dots[0b11] << '\n';

	std::cout << "dot0       " << debug_dot0 << ' ' << debug_dot0.Size() << '\n';
	std::cout << "dot1       " << debug_dot1 << ' ' << debug_dot1.Size() << '\n';
	std::cout << "dot        " << debug_dot << ' ' << debug_dot.Size() << '\n';

	std::cout << '\n';
}

float Perlin2D::Calculate(VectorF2 pos) const
{
	VectorF2 posF = pos.roundF();
	VectorI2 posI = posF;
	VectorF2 rel = pos - posI;

	VectorU2 i0 = ((posI % Count) + Count) % Count;
	VectorU2 i1 = (i0 + VectorU2(1)) % Count;

	VectorF2 dirs[4];
	dirs[0b00] = Data[Count.Convert(VectorU2(i0.X, i0.Y))];
	dirs[0b01] = Data[Count.Convert(VectorU2(i1.X, i0.Y))];
	dirs[0b10] = Data[Count.Convert(VectorU2(i0.X, i1.Y))];
	dirs[0b11] = Data[Count.Convert(VectorU2(i1.X, i1.Y))];

	VectorF2 rels[4];
	rels[0b00] = VectorF2(rel.X - 0, rel.Y - 0);
	rels[0b01] = VectorF2(rel.X - 1, rel.Y - 0);
	rels[0b10] = VectorF2(rel.X - 0, rel.Y - 1);
	rels[0b11] = VectorF2(rel.X - 1, rel.Y - 1);

	float dots[4];
	dots[0b00] = VectorF2::dot(dirs[0b00], rels[0b00]);
	dots[0b01] = VectorF2::dot(dirs[0b01], rels[0b01]);
	dots[0b10] = VectorF2::dot(dirs[0b10], rels[0b10]);
	dots[0b11] = VectorF2::dot(dirs[0b11], rels[0b11]);

	float dot_0 = lerp(dots[0b00], dots[0b10], rel.Y);
	float dot_1 = lerp(dots[0b01], dots[0b11], rel.Y);

	float dot__ = lerp(dot_0, dot_1, rel.X);

	if (DebugStatus)
	{
		std::cout << Count << '\n';
		std::cout << "posF " << pos << '\n';
		std::cout << "posI " << posI << '\n';
		std::cout << "udx0 " << i0 << '\n';
		std::cout << "udx1 " << i1 << '\n';
		std::cout << "rel " << rel << '\n';
		std::cout << "dot00 " << dots[0b00] << '\n';
		std::cout << "dot01 " << dots[0b01] << '\n';
		std::cout << "dot10 " << dots[0b10] << '\n';
		std::cout << "dot11 " << dots[0b11] << '\n';
		std::cout << "dot " << dot__ << '\n';
		std::cout << '\n';
	}

	/*if ((rand() & 0xFF) == 0)
	{
		std::cout << "cell " << X0 << ' ' << Y0 << '\n';
		//std::cout << "rel        " << rel << '\n';
		//std::cout << "rels[0b00] " << rels[0b00] << ' ' << rels[0b00].length() << '\n';
		//std::cout << "rels[0b01] " << rels[0b01] << ' ' << rels[0b01].length() << '\n';
		//std::cout << "rels[0b10] " << rels[0b10] << ' ' << rels[0b10].length() << '\n';
		//std::cout << "rels[0b11] " << rels[0b11] << ' ' << rels[0b11].length() << '\n';
		std::cout << '\n';
	}*/

	//if (rel.X != 0.0f && rel.Y != 0.0f)
	{
		debug_rel.Consider(rel);

		debug_rels[0b00].Consider(rels[0b00].length());
		debug_rels[0b01].Consider(rels[0b01].length());
		debug_rels[0b10].Consider(rels[0b10].length());
		debug_rels[0b11].Consider(rels[0b11].length());

		debug_dots[0b00].Consider(dots[0b00]);
		debug_dots[0b01].Consider(dots[0b01]);
		debug_dots[0b10].Consider(dots[0b10]);
		debug_dots[0b11].Consider(dots[0b11]);

		debug_dot0.Consider(dot_0);
		debug_dot1.Consider(dot_1);
		debug_dot.Consider(dot__);
	}

	return dot__;
}
