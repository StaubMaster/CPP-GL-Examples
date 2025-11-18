#ifndef  AXIS_BOX_HPP
# define AXIS_BOX_HPP

#include "DataStruct/Point2D.hpp"



struct AxisBox1D
{
	float Min;
	float Max;

	AxisBox1D() : Min(0), Max(0) { }
	AxisBox1D(float min, float max) : Min(min), Max(max) { }
};

struct AxisBox2D
{
	Point2D Min;
	Point2D Max;

	AxisBox2D() : Min(), Max() { }
	AxisBox2D(Point2D min, Point2D max) : Min(min), Max(max) { }

	bool Intersekt(Point2D p) const
	{
		return (Min.X <= p.X && Max.X >= p.X)
			&& (Min.Y <= p.Y && Max.Y >= p.Y);
	}
};

#endif