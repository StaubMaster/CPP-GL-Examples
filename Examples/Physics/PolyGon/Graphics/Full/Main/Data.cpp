#include "PolyGon/Graphics/Full/Main/Data.hpp"



PolyGon::Full::Main::Data::Data()
	: Pos()
	, Col()
{ }
PolyGon::Full::Main::Data::Data(Point2D pos)
	: Pos(pos)
	, Col(1, 1, 1, 1)
{ }
PolyGon::Full::Main::Data::Data(Point2D pos, ColorF4 col)
	: Pos(pos)
	, Col(col)
{ }
