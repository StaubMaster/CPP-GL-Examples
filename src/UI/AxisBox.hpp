#ifndef  AXIS_BOX_HPP
# define AXIS_BOX_HPP

#include "DataStruct/Point2D.hpp"



struct AxisBox1D
{
	float Min;
	float Max;

	AxisBox1D();
	AxisBox1D(float min, float max);
};

struct AxisBox2D
{
	Point2D Min;
	Point2D Max;

	AxisBox2D();
	AxisBox2D(Point2D min, Point2D max);

	bool Intersekt(Point2D p) const;
};

#endif