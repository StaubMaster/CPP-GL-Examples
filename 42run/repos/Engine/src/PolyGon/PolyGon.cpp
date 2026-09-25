#include "PolyGon/PolyGon.hpp"

#include "ValueType/Ray/F2.hpp"
#include "ValueType/Line/F2.hpp"
#include "ValueType/Box/F2.hpp"
#include "ValueType/Intersect.hpp"



PolyGon::Corner::Corner()
	: Pos()
	, Col()
{ }
PolyGon::Corner::Corner(VectorF2 pos)
	: Pos(pos)
	, Col()
{ }
PolyGon::Corner::Corner(VectorF2 pos, ColorF4 col)
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
void PolyGon::NewCorner(VectorF2 pos, ColorF4 col)
{
	unsigned int c_idx = Corners.Count();
	Corners.Insert(Corner(pos, col));

	// new edge from the prev last to the curr last
	// edge from the new last to the first
	if (c_idx != 0 && Edges.Count() != 0)
	{
		//Edges.MaxItem().udx[1] = c_idx;
		Edges[Edges.Count() - 1].udx[1] = c_idx;
	}
	Edges.Insert(Edge(c_idx, 0));
}
void PolyGon::NewFace(unsigned int c0, unsigned int c1, unsigned int c2)
{
	Faces.Insert(Face(c0, c1, c2));
}



BoxF2 PolyGon::ToAxisBox() const
{
	BoxF2 box;
	for (unsigned int i = 0; i < Corners.Count(); i++)
	{
		box.Consider(Corners[i].Pos);
	}
	return box;
}
Container::Array<PolyGonFull::Main::Data> PolyGon::ToFullData() const
{
	Container::Array<PolyGonFull::Main::Data> data(Faces.Count() * 3);

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





unsigned int PolyGon::SumIntersections(RayF2 ray) const
{
	unsigned int sum = 0;
	for (unsigned int f = 0; f < Faces.Count(); f++)
	{
		const Face & face = Faces[f];
		if (face.Check(Corners.Count()))
		{
			VectorF2 corner0 = Corners[face.udx[0]].Pos;
			VectorF2 corner1 = Corners[face.udx[1]].Pos;
			VectorF2 corner2 = Corners[face.udx[2]].Pos;

			if (::IsIntersecting(ray, LineF2(corner0, corner1))) { sum++; }
			if (::IsIntersecting(ray, LineF2(corner1, corner2))) { sum++; }
			if (::IsIntersecting(ray, LineF2(corner2, corner0))) { sum++; }
		}
	}
	return sum;
}
bool PolyGon::IsContaining(VectorF2 p) const
{
	return ((SumIntersections(RayF2(p, VectorF2(1, 0))) % 2) != 0);
}
