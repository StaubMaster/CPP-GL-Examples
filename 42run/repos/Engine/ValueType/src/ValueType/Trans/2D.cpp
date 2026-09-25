#include "ValueType/Trans/2D.hpp"
#include "ValueType/Ray/F2.hpp"



Trans2D::~Trans2D() { }

Trans2D::Trans2D()
	: Pos()
	, Rot()
{ }
Trans2D::Trans2D(VectorF2 pos)
	: Pos(pos)
	, Rot()
{ }
Trans2D::Trans2D(VectorF2 pos, Angle rot)
	: Pos(pos)
	, Rot(rot)
{ }

Trans2D::Trans2D(const Trans2D & other)
	: Pos(other.Pos)
	, Rot(other.Rot)
{ }
Trans2D & Trans2D::operator=(const Trans2D & other)
{
	Pos = other.Pos;
	Rot = other.Rot;
	return *this;
}



VectorF2 Trans2D::forward(VectorF2 p) const { return Rot.forward(p) + Pos; }
VectorF2 Trans2D::reverse(VectorF2 p) const { return Rot.reverse(p - Pos); }

RayF2 Trans2D::forward(RayF2 ray) const
{
	return RayF2(
		forward(ray.Pos),
		Rot.forward(ray.Dir)
	);
}
RayF2 Trans2D::reverse(RayF2 ray) const
{
	return RayF2(
		reverse(ray.Pos),
		Rot.reverse(ray.Dir)
	);
}
