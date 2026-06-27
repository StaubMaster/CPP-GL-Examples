#include "Arrow2D/Inst/Data.hpp"



Arrow2D::Inst::Data::~Data() { }
Arrow2D::Inst::Data::Data()
	: Origin()
	, Target()
	, Size(16.0f)
	, Color(1, 1, 1)
{ }



Arrow2D::Inst::Data::Data(ColorF4 col, float size, VectorF2 origin, VectorF2 target)
	: Origin(origin)
	, Target(target)
	, Size(size)
	, Color(col)
{ }
Arrow2D::Inst::Data::Data(ColorF4 col, float size, LineF2 line)
	: Origin(line.Origin)
	, Target(line.Target)
	, Size(size)
	, Color(col)
{ }
Arrow2D::Inst::Data::Data(ColorF4 col, float size, RayF2 ray)
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
Arrow2D::Inst::Data & Arrow2D::Inst::Data::operator=(const LineF2 & line)
{
	Origin = line.Origin;
	Target = line.Target;
	return *this;
}
Arrow2D::Inst::Data & Arrow2D::Inst::Data::operator=(const RayF2 & ray)
{
	Origin = ray.Pos;
	Target = ray.Pos + ray.Dir;
	return *this;
}


void Arrow2D::Inst::Data::Clear()
{
	Origin = VectorF2();
	Target = VectorF2();
}
