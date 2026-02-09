#include "CubicSpline3D.hpp"
#include "ChainNeighbours3D.hpp"



CubicSpline3D::~CubicSpline3D()
{ }
CubicSpline3D::CubicSpline3D() :
	InterPolator3D()
{ }
CubicSpline3D::CubicSpline3D(const CubicSpline3D & other) :
	InterPolator3D(),
	Pole0(other.Pole0),
	Pole1(other.Pole1)
{ }
CubicSpline3D & CubicSpline3D::operator=(const CubicSpline3D & other)
{
	Pole0 = other.Pole0;
	Pole1 = other.Pole1;
	return *this;
}



Point3D CubicSpline3D::InterPolate(float t)
{
	return (Pole0.Pos * (1 - t)) + (Pole1.Pos * (t - 0));
}



CubicSpline3D::Tangents CubicSpline3D::FiniteDifference(ChainNeighbours3D neighbours)
{
	Tangents	tans;
	Point3D		dir;
	if (neighbours.Prev != nullptr && neighbours.Next != nullptr)		//  Middle
	{
		dir = (*neighbours.Next) - (*neighbours.Prev);
	}
	else if (neighbours.Prev == nullptr && neighbours.Next != nullptr)	//  First
	{
		dir = (*neighbours.Next) - (neighbours.Here);
	}
	else if (neighbours.Prev != nullptr && neighbours.Next == nullptr)	//  Last
	{
		dir = (neighbours.Here) - (*neighbours.Prev);
	}
	else	//  Only
	{ }
	tans.Dir0 = dir;
	tans.Dir1 = dir;
	return tans;
}
//CubicSpline3D::Tangents CubicSpline3D::CatmullRom(ChainNeighbours3D neighbours, float Tk)
//CubicSpline3D::Tangents CubicSpline3D::Cardinal(ChainNeighbours3D neighbours, float ck)
//CubicSpline3D::Tangents CubicSpline3D::KochanekBartels(ChainNeighbours3D neighbours, FactorsTCB tcb)
