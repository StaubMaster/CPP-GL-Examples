#ifndef  CUBIC_SPLINE_CURVE_3D_HPP
# define CUBIC_SPLINE_CURVE_3D_HPP

# include "CubicSpline3D.hpp"
# include "Interpolator3D.hpp"
# include "Miscellaneous/Container/Array.hpp"

class CubicSplineCurve3D : public InterPolator3D
{
	private:
	public:
	Container::Array<Point3D>		Nodes;
	Container::Array<CubicSpline3D>	Segments;

	public:
	~CubicSplineCurve3D();
	CubicSplineCurve3D();
	CubicSplineCurve3D(const CubicSplineCurve3D & other);
	CubicSplineCurve3D & operator=(const CubicSplineCurve3D & other);

	public:
	Point3D InterPolate(float t) override;

	public:
	void FiniteDifference();
	//void CatmullRom(float Tk);
	//void Cardinal(float ck);
	//void KochanekBartels(FactorsTCB tcb);
};

#endif