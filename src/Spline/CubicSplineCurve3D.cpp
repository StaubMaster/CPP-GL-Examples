#include "CubicSplineCurve3D.hpp"
#include "ChainNeighbours3D.hpp"



CubicSplineCurve3D::~CubicSplineCurve3D()
{ }
CubicSplineCurve3D::CubicSplineCurve3D() :
	InterPolator3D(),
	Loop(true)
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



unsigned int CubicSplineCurve3D::SegmentIndex(float & t)
{
	//	Modulate t into range [ 0 ; SegmentCount - 1]
	{
		while (t < 0) { t += Segments.Count(); }
		while (t > Segments.Count()) { t -= Segments.Count(); }
	}
	return t;
}
Point3D CubicSplineCurve3D::InterPolatePos(float t)
{
	unsigned int idx = SegmentIndex(t);
	return Segments[idx].InterPolatePos(t - idx);
}
Point3D CubicSplineCurve3D::InterPolateDir(float t)
{
	unsigned int idx = SegmentIndex(t);
	return Segments[idx].InterPolateDir(t - idx);
}



Point3D * CubicSplineCurve3D::PrevNodePointer(unsigned int idx)
{
	if (idx == Nodes.MinIndex())
	{
		if (!Loop)
		{
			return nullptr;
		}
		else
		{
			return &Nodes.MaxItem();
		}
	}
	else
	{
		idx--;
		return &Nodes[idx];
	}
}
Point3D * CubicSplineCurve3D::NextNodePointer(unsigned int idx)
{
	if (idx == Nodes.MaxIndex())
	{
		if (!Loop)
		{
			return nullptr;
		}
		else
		{
			return &Nodes.MinItem();
		}
	}
	else
	{
		idx++;
		return &Nodes[idx];
	}
}

void CubicSplineCurve3D::ChangePrevPole1(unsigned int idx, Point3D pos, Point3D dir)
{
	if (idx == 0)
	{
		if (Loop)
		{
			Segments.MaxItem().Pole1.Pos = pos;
			Segments.MaxItem().Pole1.Dir = dir;
		}
	}
	else
	{
		idx -= 1;
		Segments[idx].Pole1.Pos = pos;
		Segments[idx].Pole1.Dir = dir;
	}
}
void CubicSplineCurve3D::ChangeNextPole0(unsigned int idx, Point3D pos, Point3D dir)
{
	if (idx == Segments.Count())
	{
		if (Loop)
		{
			Segments.MinItem().Pole0.Pos = pos;
			Segments.MinItem().Pole0.Dir = dir;
		}
	}
	else
	{
		idx -= 0;
		Segments[idx].Pole0.Pos = pos;
		Segments[idx].Pole0.Dir = dir;
	}
}

void CubicSplineCurve3D::FiniteDifference()
{
	if (Nodes.Count() <= 1) { return; }

	if (Loop)
	{ Segments.Allocate(Nodes.Count(), Nodes.Count()); }
	else
	{ Segments.Allocate(Nodes.Count() - 1, Nodes.Count() - 1); }

	ChainNeighbours3D		neighbours;
	CubicSpline3D::Tangents		tans;

	for (unsigned int i = 0; i < Nodes.Count(); i++)
	{
		neighbours.Prev = PrevNodePointer(i);
		neighbours.Here = Nodes[i];
		neighbours.Next = NextNodePointer(i);

		tans = CubicSpline3D::FiniteDifference(neighbours);

		ChangePrevPole1(i, Nodes[i], tans.Dir1);
		ChangeNextPole0(i, Nodes[i], tans.Dir0);
	}
}
//void CubicSplineCurve3D::CatmullRom(ChainNeighbours3D neighbours, float Tk);
//void CubicSplineCurve3D::Cardinal(ChainNeighbours3D neighbours, float ck);
//void CubicSplineCurve3D::KochanekBartels(ChainNeighbours3D neighbours, FactorsTCB tcb);
