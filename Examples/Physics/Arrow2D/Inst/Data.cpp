#include "Arrow2D/Inst/Data.hpp"



Arrow2D::Inst::Data::Data()
	: Pos0()
	, Pos1()
	, Size()
{ }
Arrow2D::Inst::Data::Data(Point2D pos0, Point2D pos1)
	: Pos0(pos0)
	, Pos1(pos1)
	, Size()
{ }
Arrow2D::Inst::Data::Data(Point2D pos0, Point2D pos1, float size)
	: Pos0(pos0)
	, Pos1(pos1)
	, Size(size)
{ }
Arrow2D::Inst::Data::Data(Point2D pos0, Point2D pos1, float size, ColorF4 col)
	: Pos0(pos0)
	, Pos1(pos1)
	, Size(size)
	, Col(col)
{ }

Arrow2D::Inst::Data::Data(ColorF4 col, float size, Point2D pos0, Point2D pos1)
	: Pos0(pos0)
	, Pos1(pos1)
	, Size(size)
	, Col(col)
{ }
Arrow2D::Inst::Data::Data(ColorF4 col, float size, Line2D line)
	: Pos0(line.Pos0)
	, Pos1(line.Pos1)
	, Size(size)
	, Col(col)
{ }
Arrow2D::Inst::Data::Data(ColorF4 col, float size, Ray2D ray)
	: Pos0(ray.Pos)
	, Pos1(ray.Pos + ray.Dir)
	, Size(size)
	, Col(col)
{ }
