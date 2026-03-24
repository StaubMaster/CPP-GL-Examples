#include "PolyGon/Object.hpp"

#include "ValueType/Ray2D.hpp"
#include "ValueType/Line2D.hpp"
#include "ValueType/AxisBox2D.hpp"
#include "ValueType/Intersect.hpp"



PolyGon::Object::Corner::Corner()
	: Pos()
	, Col()
{ }
PolyGon::Object::Corner::Corner(Point2D pos)
	: Pos(pos)
	, Col()
{ }
PolyGon::Object::Corner::Corner(Point2D pos, ColorF4 col)
	: Pos(pos)
	, Col(col)
{ }



bool PolyGon::Object::Face::Check(unsigned int count) const
{
	return (udx[0] < count &&
			udx[1] < count &&
			udx[2] < count);
}
PolyGon::Object::Face::Face()
	: udx
	{
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
	}
{ }
PolyGon::Object::Face::Face(unsigned int u0, unsigned int u1, unsigned int u2)
	: udx{ u0, u1, u2 }
{ }



bool PolyGon::Object::Edge::Check(unsigned int count) const
{
	return (udx[0] < count &&
			udx[1] < count);
}
PolyGon::Object::Edge::Edge()
	: udx
	{
		0xFFFFFFFF,
		0xFFFFFFFF,
	}
{ }
PolyGon::Object::Edge::Edge(unsigned int u0, unsigned int u1)
	: udx{ u0, u1 }
{ }





PolyGon::Object::Object()
	: Corners()
	, Faces()
	, Edges()
{ }
PolyGon::Object::~Object()
{ }



void PolyGon::Object::Clear()
{
	Corners.Clear();
	Faces.Clear();
	Edges.Clear();
}
void PolyGon::Object::NewCorner(Point2D pos, ColorF4 col)
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
void PolyGon::Object::NewFace(unsigned int c0, unsigned int c1, unsigned int c2)
{
	Faces.Insert(Face(c0, c1, c2));
}



AxisBox2D PolyGon::Object::ToAxisBox() const
{
	AxisBox2D box;
	for (unsigned int i = 0; i < Corners.Count(); i++)
	{
		box.Consider(Corners[i].Pos);
	}
	return box;
}
Container::Pointer<PolyGon::Full::Main::Data> PolyGon::Object::ToFullData() const
{
	Container::Pointer<PolyGon::Full::Main::Data> data(Faces.Count() * 3);

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





unsigned int PolyGon::Object::SumIntersections(Ray2D ray) const
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
bool PolyGon::Object::IsContaining(Point2D p) const
{
	return ((SumIntersections(Ray2D(p, Point2D(1, 0))) % 2) != 0);
}
