#include "WireFrame2D/WireFrame2D.hpp"



WireFrame2D::Corner::Corner()
	: Pos()
	, Col()
{ }
WireFrame2D::Corner::Corner(Point2D pos)
	: Pos(pos)
	, Col()
{ }
WireFrame2D::Corner::Corner(Point2D pos, ColorF4 col)
	: Pos(pos)
	, Col(col)
{ }

WireFrame2D::Side::Side()
	: udx{ 0, 0 }
{ }
WireFrame2D::Side::Side(unsigned int udx0, unsigned int udx1)
	: udx{ udx0, udx1 }
{ }



WireFrame2D::~WireFrame2D() { }
WireFrame2D::WireFrame2D()
	: Corners()
	, Sides()
{ }



void WireFrame2D::Clear()
{
	Corners.Clear();
	Sides.Clear();
}
