#include "Arrow2D/Inst/Data.hpp"



Arrow2D::Inst::Data::~Data() { }
Arrow2D::Inst::Data::Data()
	: Origin()
	, Target()
	, Size(16.0f)
	, Color(1, 1, 1)
{ }



Arrow2D::Inst::Data::Data(ColorF4 col, float size, Point2D origin, Point2D target)
	: Origin(origin)
	, Target(target)
	, Size(size)
	, Color(col)
{ }
Arrow2D::Inst::Data::Data(ColorF4 col, float size, Line2D line)
	: Origin(line.Pos0)
	, Target(line.Pos1)
	, Size(size)
	, Color(col)
{ }
Arrow2D::Inst::Data::Data(ColorF4 col, float size, Ray2D ray)
	: Origin(ray.Pos)
	, Target(ray.Pos + ray.Dir)
	, Size(size)
	, Color(col)
{ }



Arrow2D::Inst::Data & Arrow2D::Inst::Data::operator=(const float & size)
{
	Size = size;
	return *this;
}
Arrow2D::Inst::Data & Arrow2D::Inst::Data::operator=(const ColorF4 & color)
{
	Color = color;
	return *this;
}
Arrow2D::Inst::Data & Arrow2D::Inst::Data::operator=(const Line2D & line)
{
	Origin = line.Pos0;
	Target = line.Pos1;
	return *this;
}
Arrow2D::Inst::Data & Arrow2D::Inst::Data::operator=(const Ray2D & ray)
{
	Origin = ray.Pos;
	Target = ray.Pos + ray.Dir;
	return *this;
}


void Arrow2D::Inst::Data::Clear()
{
	Origin = Point2D();
	Target = Point2D();
}
