#include "Grid2D/Grid2D.hpp"
#include <math.h>



Grid2D::~Grid2D() { }
Grid2D::Grid2D()
	: Lin(1.0f)
	, Ang(1.0f)
{ }
Grid2D::Grid2D(float lin, float ang)
	: Lin(lin)
	, Ang(ang)
{ }



Point2D Grid2D::Align(Point2D p) const
{
	p /= Lin;
	p.X = roundf(p.X);
	p.Y = roundf(p.Y);
	p *= Lin;
	return p;
}
Angle2D Grid2D::Align(Angle2D a) const
{
	a /= Ang;
	a.Ang.FromDegrees(roundf(a.Ang.ToDegrees()));
	a *= Ang;
	a.CalcMatrix();
	return a;
}
