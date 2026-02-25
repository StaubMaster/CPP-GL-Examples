#include "PolyGon/Graphics/Data.hpp"



PolyGonGraphics::Data::Data()
	: Pos()
	, Col()
{ }
PolyGonGraphics::Data::Data(Point2D pos)
	: Pos(pos)
	, Col(1, 1, 1, 1)
{ }
PolyGonGraphics::Data::Data(Point2D pos, ColorF4 col)
	: Pos(pos)
	, Col(col)
{ }
