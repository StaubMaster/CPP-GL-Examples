#include "PolyGon/Data.hpp"



PolyGon::Corner::Corner()
	: Pos()
	, Col()
{ }
PolyGon::Corner::Corner(Point2D pos)
	: Pos(pos)
	, Col()
{ }
PolyGon::Corner::Corner(Point2D pos, ColorF4 col)
	: Pos(pos)
	, Col(col)
{ }



PolyGon::SideCorner::SideCorner()
	: Udx(0)
{ }
PolyGon::SideCorner::SideCorner(unsigned int udx)
	: Udx(udx)
{ }



PolyGon::Side::Side()
	: Corner0()
	, Corner1()
	, Corner2()
{ }
PolyGon::Side::Side(SideCorner c0, SideCorner c1, SideCorner c2)
	: Corner0(c0)
	, Corner1(c1)
	, Corner2(c2)
{ }
