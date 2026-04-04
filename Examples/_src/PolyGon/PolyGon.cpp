#include "PolyGon/PolyGon.hpp"

#include "ValueType/Ray2D.hpp"
#include "ValueType/Line2D.hpp"
#include "ValueType/AxisBox2D.hpp"
#include "ValueType/Intersect.hpp"



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



bool PolyGon::Face::Check(unsigned int count) const
{
	return (udx[0] < count &&
			udx[1] < count &&
			udx[2] < count);
}
PolyGon::Face::Face()
	: udx
	{
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
	}
{ }
PolyGon::Face::Face(unsigned int u0, unsigned int u1, unsigned int u2)
	: udx{ u0, u1, u2 }
{ }



bool PolyGon::Edge::Check(unsigned int count) const
{
	return (udx[0] < count &&
			udx[1] < count);
}
PolyGon::Edge::Edge()
	: udx
	{
		0xFFFFFFFF,
		0xFFFFFFFF,
	}
{ }
PolyGon::Edge::Edge(unsigned int u0, unsigned int u1)
	: udx{ u0, u1 }
{ }





PolyGon::PolyGon()
	: Corners()
	, Faces()
	, Edges()
{ }
PolyGon::~PolyGon()
{ }



void PolyGon::Clear()
{
	Corners.Clear();
	Faces.Clear();
	Edges.Clear();
}
void PolyGon::NewCorner(Point2D pos, ColorF4 col)
{
	unsigned int c_idx = Corners.Count();
	Corners.Insert(Corner(pos, col));

	// new edge from the prev last to the curr last
	// edge from the new last to the first
	if (c_idx != 0 && Edges.Count() != 0)
	{
		Edges.MaxItem().udx[1] = c_idx;
	}
	Edges.Insert(Edge(c_idx, 0));
}
void PolyGon::NewFace(unsigned int c0, unsigned int c1, unsigned int c2)
{
	Faces.Insert(Face(c0, c1, c2));
}



AxisBox2D PolyGon::ToAxisBox() const
{
	AxisBox2D box;
	for (unsigned int i = 0; i < Corners.Count(); i++)
	{
		box.Consider(Corners[i].Pos);
	}
	return box;
}
Container::Pointer<PolyGonFull::Main::Data> PolyGon::ToFullData() const
{
	Container::Pointer<PolyGonFull::Main::Data> data(Faces.Count() * 3);

	for (unsigned int f = 0; f < Faces.Count(); f++)
	{
		const Face & face = Faces[f];
		if (face.Check(Corners.Count()))
		{
			int c = f * 3;
			const Corner & corner0 = Corners[face.udx[0]];
			const Corner & corner1 = Corners[face.udx[1]];
			const Corner & corner2 = Corners[face.udx[2]];

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





unsigned int PolyGon::SumIntersections(Ray2D ray) const
{
	unsigned int sum = 0;
	for (unsigned int f = 0; f < Faces.Count(); f++)
	{
		const Face & face = Faces[f];
		if (face.Check(Corners.Count()))
		{
			Point2D corner0 = Corners[face.udx[0]].Pos;
			Point2D corner1 = Corners[face.udx[1]].Pos;
			Point2D corner2 = Corners[face.udx[2]].Pos;

			if (::IsIntersecting(ray, Line2D(corner0, corner1))) { sum++; }
			if (::IsIntersecting(ray, Line2D(corner1, corner2))) { sum++; }
			if (::IsIntersecting(ray, Line2D(corner2, corner0))) { sum++; }
		}
	}
	return sum;
}
bool PolyGon::IsContaining(Point2D p) const
{
	return ((SumIntersections(Ray2D(p, Point2D(1, 0))) % 2) != 0);
}
