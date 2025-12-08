#include "AxisBox.hpp"



AxisBox1D::AxisBox1D() : Min(0), Max(0) { }
AxisBox1D::AxisBox1D(float min, float max) : Min(min), Max(max) { }



AxisBox2D::AxisBox2D() : Min(), Max() { }
AxisBox2D::AxisBox2D(Point2D min, Point2D max) : Min(min), Max(max) { }

bool AxisBox2D::Intersekt(Point2D p) const
{
	return (Min.X <= p.X && Max.X >= p.X)
		&& (Min.Y <= p.Y && Max.Y >= p.Y);
}
