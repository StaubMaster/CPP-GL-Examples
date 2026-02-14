#include "PolyGon/Main/Data.hpp"



Physics2D::Main::Data::Data()
	: Pos()
	, Col()
{ }
Physics2D::Main::Data::Data(Point2D pos)
	: Pos(pos)
	, Col(1, 1, 1, 1)
{ }
Physics2D::Main::Data::Data(Point2D pos, ColorF4 col)
	: Pos(pos)
	, Col(col)
{ }
