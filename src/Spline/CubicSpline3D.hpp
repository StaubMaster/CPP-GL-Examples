#ifndef  CUBIC_SPLINE_3D_HPP
# define CUBIC_SPLINE_3D_HPP

# include "InterPolator3D.hpp"
# include "ValueType/Point3D.hpp"

struct ChainNeighbours3D;

class CubicSpline3D : public InterPolator3D
{
	public:
	struct Pole
	{
		Point3D	Pos;
		Point3D	Dir;
	};
	Pole	Pole0;
	Pole	Pole1;

	public:
	~CubicSpline3D();
	CubicSpline3D();
	CubicSpline3D(const CubicSpline3D & other);
	CubicSpline3D & operator=(const CubicSpline3D & other);

	public:
	Point3D InterPolatePos(float t) override;
	Point3D InterPolateDir(float t) override;

	public:
	struct Tangents
	{
		Point3D Dir0;
		Point3D Dir1;
	};
	struct FactorsTCB
	{
		float T;
		float C;
		float B;
	};
	static Tangents FiniteDifference(ChainNeighbours3D neighbours);
	//static Tangents CatmullRom(ChainNeighbours3D neighbours, float Tk);
	//static Tangents Cardinal(ChainNeighbours3D neighbours, float ck);
	//static Tangents KochanekBartels(ChainNeighbours3D neighbours, FactorsTCB tcb);
};

#endif