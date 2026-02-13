#include "PolyGon.hpp"



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



PolyGon::PolyGon()
	: Corners()
	, Sides()
{ }
PolyGon::~PolyGon()
{ }



void PolyGon::Clear()
{
	Corners.Clear();
	Sides.Clear();
}



Container::Pointer<Physics2D::Main::Data> PolyGon::ToPhysics2D() const
{
	Container::Pointer<Physics2D::Main::Data> data(Sides.Count() * 3);

	for (unsigned int f = 0; f < Sides.Count(); f++)
	{
		const Side & side = Sides[f];
		int c = f * 3;
		if (side.Corner0.Udx < Corners.Count() &&
			side.Corner1.Udx < Corners.Count() &&
			side.Corner2.Udx < Corners.Count())
		{
			const Corner & corner0 = Corners[side.Corner0.Udx];
			const Corner & corner1 = Corners[side.Corner1.Udx];
			const Corner & corner2 = Corners[side.Corner2.Udx];

			data[c + 0].Pos = corner0.Pos;
			data[c + 2].Pos = corner1.Pos;
			data[c + 1].Pos = corner2.Pos;

			data[c + 0].Col = corner0.Col;
			data[c + 2].Col = corner1.Col;
			data[c + 1].Col = corner2.Col;
		}
	}

	return data;
}
