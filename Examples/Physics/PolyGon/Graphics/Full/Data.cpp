#include "PolyGon/Graphics/Full/Data.hpp"



PolyGon::Full::Data::Data()
	: Pos()
	, Col()
{ }
PolyGon::Full::Data::Data(Point2D pos)
	: Pos(pos)
	, Col(1, 1, 1, 1)
{ }
PolyGon::Full::Data::Data(Point2D pos, ColorF4 col)
	: Pos(pos)
	, Col(col)
{ }
