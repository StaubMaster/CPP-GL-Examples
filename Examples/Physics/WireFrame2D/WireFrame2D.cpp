#include "WireFrame2D/WireFrame2D.hpp"
#include "ValueType/AxisBox2D.hpp"



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



void WireFrame2D::Insert_Corner(Point2D pos) { Corners.Insert(Corner(pos)); }
void WireFrame2D::Insert_Corner(Point2D pos, ColorF4 col) { Corners.Insert(Corner(pos, col)); }
void WireFrame2D::Insert_Side(unsigned int udx0, unsigned int udx1) { Sides.Insert(Side(udx0, udx1)); }

void WireFrame2D::Insert_Box(AxisBox2D box, ColorF4 col)
{
	Insert_Corner(Point2D(box.Min.X, box.Min.Y), col);
	Insert_Corner(Point2D(box.Max.X, box.Min.Y), col);
	Insert_Corner(Point2D(box.Max.X, box.Max.Y), col);
	Insert_Corner(Point2D(box.Min.X, box.Max.Y), col);

	unsigned int idx = Sides.Count();
	Insert_Side(idx + 0, idx + 1);
	Insert_Side(idx + 1, idx + 2);
	Insert_Side(idx + 2, idx + 3);
	Insert_Side(idx + 3, idx + 0);
}
