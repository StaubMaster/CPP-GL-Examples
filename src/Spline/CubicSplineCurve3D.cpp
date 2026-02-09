#include "CubicSplineCurve3D.hpp"
#include "ChainNeighbours3D.hpp"



CubicSplineCurve3D::~CubicSplineCurve3D()
{ }
CubicSplineCurve3D::CubicSplineCurve3D() :
	InterPolator3D()
{ }
CubicSplineCurve3D::CubicSplineCurve3D(const CubicSplineCurve3D & other) :
	InterPolator3D(),
	Nodes(other.Nodes.Copy()),
	Segments(other.Segments.Copy())
{ }
CubicSplineCurve3D & CubicSplineCurve3D::operator=(const CubicSplineCurve3D & other)
{
	Nodes.Copy(other.Nodes);
	Segments.Copy(other.Segments);
	return *this;
}



Point3D CubicSplineCurve3D::InterPolate(float t)
{
	//	Modulate t into range [ 0 ; SegmentCount - 1]
	{
		while (t < 0) { t += Segments.Count(); }
		while (t > Segments.Count()) { t -= Segments.Count(); }
	}
	unsigned int idx = t;
	return Segments[idx].InterPolate(t - idx);
}



void CubicSplineCurve3D::FiniteDifference()
{
	if (Nodes.Count() <= 1)
	{
		return;
	}

	//	NoLoop
	{
		Segments.Allocate(Nodes.Count() - 1, Nodes.Count() - 1);

		ChainNeighbours3D	neighbours;
		CubicSpline3D::Tangents	tans;

		//	First
		{
			unsigned int i = 0;
			neighbours.Prev = nullptr;
			neighbours.Here = Nodes[i];
			neighbours.Next = &Nodes[i + 1];
			tans = CubicSpline3D::FiniteDifference(neighbours);
			Segments[i - 0].Pole0.Pos = Nodes[i];
			Segments[i - 0].Pole0.Dir = tans.Dir0;
		}
		for (unsigned int i = 1; i < Nodes.Count() - 1; i++)
		{
			neighbours.Prev = &Nodes[i - 1];
			neighbours.Here = Nodes[i];
			neighbours.Next = &Nodes[i + 1];
			tans = CubicSpline3D::FiniteDifference(neighbours);
			Segments[i - 1].Pole1.Pos = Nodes[i];
			Segments[i - 1].Pole1.Dir = tans.Dir1;
			Segments[i - 0].Pole0.Pos = Nodes[i];
			Segments[i - 0].Pole0.Dir = tans.Dir0;
		}
		//	Last
		{
			unsigned int i = Nodes.Count() - 1;
			neighbours.Prev = &Nodes[i - 1];
			neighbours.Here = Nodes[i];
			neighbours.Next = nullptr;
			tans = CubicSpline3D::FiniteDifference(neighbours);
			Segments[i - 1].Pole1.Pos = Nodes[i];
			Segments[i - 1].Pole1.Dir = tans.Dir1;
		}
	}
}
//void CubicSplineCurve3D::CatmullRom(ChainNeighbours3D neighbours, float Tk);
//void CubicSplineCurve3D::Cardinal(ChainNeighbours3D neighbours, float ck);
//void CubicSplineCurve3D::KochanekBartels(ChainNeighbours3D neighbours, FactorsTCB tcb);
