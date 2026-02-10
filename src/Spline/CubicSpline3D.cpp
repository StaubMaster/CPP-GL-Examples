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



Point3D CubicSpline3D::InterPolatePos(float t)
{
	float factors_pos[4];
	{
		float t0 = 1;		//  t^0
		float t1 = t0 * t;	//  t^1
		float t2 = t1 * t;	//  t^2
		float t3 = t2 * t;	//  t^3
		factors_pos[0] = (2 * t3) - (3 * t2) + (1 * t0);
		factors_pos[1] = t3 - (2 * t2) + t1;
		factors_pos[2] = -(2 * t3) + (3 * t2);
		factors_pos[3] = t3 - t2;
	}
	Point3D pos;
	pos += Pole0.Pos * factors_pos[0];
	pos += Pole0.Dir * factors_pos[1];
	pos += Pole1.Pos * factors_pos[2];
	pos += Pole1.Dir * factors_pos[3];
	return pos;
}
Point3D CubicSpline3D::InterPolateDir(float t)
{
	float factors_dir[4];
	{
		//	Derivative
		float t0 = 0;			//  t^0    0 * ?
		float t1 = 1;			//  t^1    1 * t^0
		float t2 = 2 * t;		//  t^2    2 * t^1
		float t3 = 3 * t * t;	//  t^3    3 * t^2
		factors_dir[0] = (2 * t3) - (3 * t2) + (1 * t0);
		factors_dir[1] = t3 - (2 * t2) + t1;
		factors_dir[2] = -(2 * t3) + (3 * t2);
		factors_dir[3] = t3 - t2;
	}
	Point3D dir;
	dir += Pole0.Pos * factors_dir[0];
	dir += Pole0.Dir * factors_dir[1];
	dir += Pole1.Pos * factors_dir[2];
	dir += Pole1.Dir * factors_dir[3];
	return dir;
}



CubicSpline3D::Tangents CubicSpline3D::FiniteDifference(ChainNeighbours3D neighbours)
{
	Tangents	tans;
	Point3D		dir;
	if (neighbours.Prev != nullptr && neighbours.Next != nullptr)
	{
		dir = (*neighbours.Next) - (*neighbours.Prev);
	}
	else if (neighbours.Prev == nullptr && neighbours.Next != nullptr)
	{
		dir = (*neighbours.Next) - (neighbours.Here);
	}
	else if (neighbours.Prev != nullptr && neighbours.Next == nullptr)
	{
		dir = (neighbours.Here) - (*neighbours.Prev);
	}
	else
	{ }
	tans.Dir0 = dir;
	tans.Dir1 = dir;
	return tans;
}
//CubicSpline3D::Tangents CubicSpline3D::CatmullRom(ChainNeighbours3D neighbours, float Tk)
//CubicSpline3D::Tangents CubicSpline3D::Cardinal(ChainNeighbours3D neighbours, float ck)
CubicSpline3D::Tangents CubicSpline3D::KochanekBartels(ChainNeighbours3D neighbours, FactorsTCB tcb)
{
	Tangents	tans;
	Point3D		dirPrev;
	Point3D		dirNext;

	if (neighbours.Prev != nullptr && neighbours.Next != nullptr)
	{
		dirPrev = (neighbours.Here) - (*neighbours.Prev);
		dirNext = (*neighbours.Next) - (neighbours.Here);
	}
	else if (neighbours.Prev == nullptr && neighbours.Next != nullptr)
	{
		dirNext = (*neighbours.Next) - (neighbours.Here);
		dirPrev = dirNext;
	}
	else if (neighbours.Prev != nullptr && neighbours.Next == nullptr)
	{
		dirPrev = (neighbours.Here) - (*neighbours.Prev);
		dirNext = dirPrev;
	}
	else
	{ }

	float factorsTCB[4];
	{
		float Tm = 1 - tcb.T;
		float Cm = 1 - tcb.C;
		float Cp = 1 + tcb.C;
		float Bm = 1 - tcb.B;
		float Bp = 1 + tcb.B;

		factorsTCB[0] = (Tm * Cm * Bp) / 2;
		factorsTCB[1] = (Tm * Cp * Bm) / 2;
		factorsTCB[2] = (Tm * Cp * Bp) / 2;
		factorsTCB[3] = (Tm * Cm * Bm) / 2;
	};

	tans.Dir0 = dirPrev * factorsTCB[0] + dirNext * factorsTCB[1];
	tans.Dir1 = dirPrev * factorsTCB[2] + dirNext * factorsTCB[3];
	return tans;
}
