#include "PolyGon/Graphics/Full/Main/Data.hpp"



PolyGonFull::Main::Data::Data()
	: Pos()
	, Col()
{ }
PolyGonFull::Main::Data::Data(Point2D pos)
	: Pos(pos)
	, Col(1, 1, 1, 1)
{ }
PolyGonFull::Main::Data::Data(Point2D pos, ColorF4 col)
	: Pos(pos)
	, Col(col)
{ }
