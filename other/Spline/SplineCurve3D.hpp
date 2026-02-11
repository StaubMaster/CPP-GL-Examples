#ifndef  SPLINE_CURVE_3D_HPP
# define SPLINE_CURVE_3D_HPP

# include "SplineSegment3D.hpp"
# include "SplineNode3D.hpp"

struct SplineCurve3D
{
	SplineSegment3D	* Segments;
	unsigned int SegmentCount;

	float T;
	float B;
	float C;

	void SetT(float val);
	void SetB(float val);
	void SetC(float val);

	void CalcTBCFromSegments();

	SplineCurve3D(SplineNode3D * nodes, unsigned int count, bool closed, float t, float b, float c);
	~SplineCurve3D();

	unsigned int	FindSegmentIndex(float & t) const;

	SplineNode3D	InterpolateLinear(float t) const;
	SplineNode3D	InterpolateCubicHermite(float t) const;
	SplineNode3D	InterpolateFiniteDifference(float t) const;
	SplineNode3D	InterpolateKochanekBartels(float t) const;

	SplineNode3D	Interpolate0(float t) const;
	SplineNode3D	Interpolate1(float t) const;
};

#endif