#ifndef  SPLINE_SEGMENT_3D_HPP
# define SPLINE_SEGMENT_3D_HPP

# include "SplineNode3D.hpp"

struct SplineSegment3D
{
	SplineNode3D	Node0;
	SplineNode3D	Node1;
	SplineSegment3D *	Prev;
	SplineSegment3D *	Next;

	float	T;	//Tension
	float	B;	//Bias
	float	C;	//Continuity

	SplineSegment3D();
	SplineSegment3D(SplineNode3D node0, SplineNode3D node1, float t, float b, float c);

	SplineNode3D	Calculate(float t) const;
	SplineNode3D	CalculateLerp(float t) const;
};

#endif