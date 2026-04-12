#include "Perlin2D.hpp"
#include "Random.hpp"
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
	, Data(new Point2D[Count.X * Count.Y])
{
	unsigned int c = Count.X * Count.Y;
	for (unsigned int i = 0; i < c; i++)
	{
		Data[i] = other.Data[i];
	}
}
Perlin2D & Perlin2D::operator=(const Perlin2D & other)
{
	delete[] Data;
	Count = other.Count;
	Data = new Point2D[Count.X * Count.Y];

	unsigned int c = Count.X * Count.Y;
	for (unsigned int i = 0; i < c; i++)
	{
		Data[i] = other.Data[i];
	}

	return *this;
}

Perlin2D::Perlin2D(Undex2D count)
	: Count(count)
	, Data(new Point2D[Count.X * Count.Y])
{ }

Perlin2D Perlin2D::Random(Undex2D count)
{
	Perlin2D perlin(count);
	unsigned int c = perlin.Count.X * perlin.Count.Y;
	for (unsigned int i = 0; i < c; i++)
	{
		Angle a = Angle::Degrees(Random::Float01In() * 360.0f);
		perlin.Data[i] = a.forward(Point2D(1, 0));
	}
	return perlin;
}

Undex2D Perlin2D::Normalize(Point2D node) const
{
	int x = node.X;
	int y = node.Y;
	while (x < 0) { x += Count.X; }
	while (y < 0) { y += Count.Y; }
	while (x >= (int)Count.X) { x -= Count.X; }
	while (y >= (int)Count.Y) { y -= Count.Y; }
	return Undex2D(x, y);
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

float Perlin2D::Calculate(Point2D pos) const
{
	int x = pos.X;
	int y = pos.Y;

	int X0 = ((x % Count.X) + Count.X) % Count.X;
	int Y0 = ((y % Count.Y) + Count.Y) % Count.Y;

	int X1 = (X0 + 1) % Count.X;
	int Y1 = (Y0 + 1) % Count.Y;

	Point2D rel(pos.X - x, pos.Y - y);

	Point2D dirs[4];
	dirs[0b00] = Data[X0 + (Y0 * Count.X)];
	dirs[0b01] = Data[X1 + (Y0 * Count.X)];
	dirs[0b10] = Data[X0 + (Y1 * Count.X)];
	dirs[0b11] = Data[X1 + (Y1 * Count.X)];

	Point2D rels[4];
	rels[0b00] = Point2D(rel.X - 0, rel.Y - 0);
	rels[0b01] = Point2D(rel.X - 1, rel.Y - 0);
	rels[0b10] = Point2D(rel.X - 0, rel.Y - 1);
	rels[0b11] = Point2D(rel.X - 1, rel.Y - 1);

	float dots[4];
	dots[0b00] = Point2D::dot(dirs[0b00], rels[0b00]);
	dots[0b01] = Point2D::dot(dirs[0b01], rels[0b01]);
	dots[0b10] = Point2D::dot(dirs[0b10], rels[0b10]);
	dots[0b11] = Point2D::dot(dirs[0b11], rels[0b11]);

	//float sqrt2 = 1.41421356237f;

	float dot0 = lerp(dots[0b00], dots[0b01], rel.X);
	float dot1 = lerp(dots[0b10], dots[0b11], rel.X);
	float dot = lerp(dot0, dot1, rel.Y);

	if (DebugStatus)
	{
		std::cout << Count << '\n';
		std::cout << "posF " << pos << '\n';
		std::cout << "posI " << x << ' ' << y << '\n';
		std::cout << "udx0 " << X0 << ' ' << Y0 << '\n';
		std::cout << "udx1 " << X1 << ' ' << Y1 << '\n';
		std::cout << "rel " << rel << '\n';
		std::cout << "dot00 " << dots[0b00] << '\n';
		std::cout << "dot01 " << dots[0b01] << '\n';
		std::cout << "dot10 " << dots[0b10] << '\n';
		std::cout << "dot11 " << dots[0b11] << '\n';
		std::cout << "dot " << dot << '\n';
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

		debug_dot0.Consider(dot0);
		debug_dot1.Consider(dot1);
		debug_dot.Consider(dot);
	}

	return dot;
}
