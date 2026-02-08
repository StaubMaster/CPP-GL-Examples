#ifndef  CUBIC_SPLINE_CURVE_3D_HPP
# define CUBIC_SPLINE_CURVE_3D_HPP

# include "CubicSpline3D.hpp"
# include "Interpolator3D.hpp"

class CubicSplineCurve3D : public InterPolator3D
{
	private:

	public:
	Point3D InterPolate(float t) override;
};
