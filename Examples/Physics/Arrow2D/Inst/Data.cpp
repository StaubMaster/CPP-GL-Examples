#include "Arrow2D/Inst/Data.hpp"



Arrow2D::Inst::Data::Data()
	: Pos()
	, Dir()
	, Size()
{ }
Arrow2D::Inst::Data::Data(Point2D pos, Point2D dir)
	: Pos(pos)
	, Dir(dir)
	, Size()
{ }
Arrow2D::Inst::Data::Data(Point2D pos, Point2D dir, float size)
	: Pos(pos)
	, Dir(dir)
	, Size(size)
{ }
