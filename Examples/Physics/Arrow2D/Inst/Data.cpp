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
Arrow2D::Inst::Data::Data(Line2D line, float size, ColorF4 col)
	: Pos0(line.Pos0)
	, Pos1(line.Pos1)
	, Size(size)
	, Col(col)
{ }
