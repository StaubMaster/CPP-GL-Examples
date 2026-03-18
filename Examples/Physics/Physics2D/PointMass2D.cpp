#include "Physics2D/PointMass2D.hpp"



PointMass2D::~PointMass2D() { }
PointMass2D::PointMass2D()
	: Point()
	, Mass(0.0f)
{ }
PointMass2D::PointMass2D(Point2D point, float mass)
	: Point(point)
	, Mass(mass)
{ }

PointMass2D::PointMass2D(const PointMass2D & other)
	: Point(other.Point)
	, Mass(other.Mass)
{ }
PointMass2D & PointMass2D::operator=(const PointMass2D & other)
{
	Point = other.Point;
	Mass = other.Mass;
	return *this;
}



float PointMass2D::Area(const Container::Member<PointMass2D> & point_masses)
{
	float Area = 0.0f;
	for (unsigned int i = 0; i < point_masses.Count(); i++)
	{
		Point2D p0, p1;
		if (i == 0)
		{
			p0 = point_masses[point_masses.Count() - 1].Point;
			p1 = point_masses[0].Point;
		}
		else
		{
			p0 = point_masses[i - 1].Point;
			p1 = point_masses[i - 0].Point;
		}
		float a = Point2D::cross(p0, p1) * 0.5f;
		Area += a;
	}
	return Area;
}

PointMass2D PointMass2D::CenterOfMass(const Container::Member<PointMass2D> & point_masses)
{
	Point2D MassPosSum;
	float MassSum = 0.0f;
	for (unsigned int i = 0; i < point_masses.Count(); i++)
	{
		MassPosSum += point_masses[i].Point * point_masses[i].Mass;
		MassSum += point_masses[i].Mass;
	}
	return PointMass2D(MassPosSum / MassSum, MassSum);
}

float PointMass2D::MomentOfInertia(const Container::Member<PointMass2D> & point_masses)
{
	float MomentOfInertia = 0.0f;
	for (unsigned int i = 0; i < point_masses.Count(); i++)
	{
		MomentOfInertia += point_masses[i].Mass * point_masses[i].Point.length2();
	}
	return MomentOfInertia;
}



#include "ValueType/Matrix3x3.hpp"
#include "ValueType/Point3D.hpp"
Matrix3x3 PointMass2D::InertiaTensor(const Container::Member<PointMass2D> & point_masses)
{
	Matrix3x3 I;
	for (unsigned int y = 0; y < 3; y++)
	{
		for (unsigned int x = 0; x < 3; x++)
		{
			float sum = 0.0f;
			for (unsigned int n = 0; n < point_masses.Count(); n++)
			{
				Point3D rel(point_masses[n].Point.X, point_masses[n].Point.Y, 0.0f);
				float rel_[3] { rel.X, rel.Y, rel.Z };
				float val = -(rel_[x] * rel_[y]);
				if (x == y) { val += rel.length2(); }
				sum += val * point_masses[n].Mass;
			}
			I.Data[x][y] = sum;
		}
	}
	return I;
}
