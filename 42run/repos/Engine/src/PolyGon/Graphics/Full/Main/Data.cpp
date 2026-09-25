#include "PolyGon/Graphics/Full/Main/Data.hpp"



PolyGonFull::Main::Data::Data()
	: Pos()
	, Col()
{ }
PolyGonFull::Main::Data::Data(VectorF2 pos)
	: Pos(pos)
	, Col(1, 1, 1, 1)
{ }
PolyGonFull::Main::Data::Data(VectorF2 pos, ColorF4 col)
	: Pos(pos)
	, Col(col)
{ }
