#include "PolyGon.hpp"
#include "PolyGon/Data.hpp"

#include "ValueType/Ray2D.hpp"
#include "ValueType/Line2D.hpp"
#include "ValueType/Intersect.hpp"



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



Container::Pointer<PolyGonGraphics::Data> PolyGon::ToMainData() const
{
	Container::Pointer<PolyGonGraphics::Data> data(Sides.Count() * 3);

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





bool PolyGon::IsIntersecting(Ray2D ray) const
{
	unsigned int sum = 0;
	for (unsigned int i = 0; i < Sides.Count(); i++)
	{
		Point2D corner0 = Corners[(Sides[i].Corner0.Udx)].Pos;
		Point2D corner1 = Corners[(Sides[i].Corner1.Udx)].Pos;
		Point2D corner2 = Corners[(Sides[i].Corner2.Udx)].Pos;

		if (::IsIntersecting(ray, Line2D(corner0, corner1))) { sum++; }
		if (::IsIntersecting(ray, Line2D(corner1, corner2))) { sum++; }
		if (::IsIntersecting(ray, Line2D(corner2, corner0))) { sum++; }
	}
	return (sum % 2) != 0;
}
bool PolyGon::IsContaining(Point2D p) const
{
	return IsIntersecting(Ray2D(p, Point2D(1, 0)));
}
