#include "Anchor.hpp"

#include "DataStruct/Point2D.hpp"
#include "AxisBox.hpp"



AxisBox1D Anchor1D::Calculate(AxisBox1D Dist, float Size, float NormalCenter, AxisBox1D Parent)
{
	AxisBox1D child;
	if (Anchor == ANCHOR_NONE)
	{
		float t0 = (NormalCenter - 0);
		float t1 = (1 - NormalCenter);
		float center = (Parent.Min * t0) + (Parent.Max * t1);
		child.Min = center - (Size / 2);
		child.Max = center + (Size / 2);
	}
	else if (Anchor == ANCHOR_MIN)
	{
		child.Min = Parent.Min + Dist.Min;
		child.Max = Parent.Min + Dist.Min + Size;
	}
	else if (Anchor == ANCHOR_MAX)
	{
		child.Min = Parent.Max - Dist.Max - Size;
		child.Max = Parent.Max - Dist.Max;
	}
	else if (Anchor == ANCHOR_BOTH)
	{
		child.Min = Parent.Min + Dist.Min;
		child.Max = Parent.Max - Dist.Max;
	}
	return child;
}



AxisBox2D Anchor2D::Calculate(AxisBox2D Dist, Point2D Size, Point2D NormalCenter, AxisBox2D Parent)
{
	AxisBox1D x = X.Calculate(AxisBox1D(Dist.Min.X, Dist.Max.X), Size.X, NormalCenter.X, AxisBox1D(Parent.Min.X, Parent.Max.X));
	AxisBox1D y = Y.Calculate(AxisBox1D(Dist.Min.Y, Dist.Max.Y), Size.Y, NormalCenter.Y, AxisBox1D(Parent.Min.Y, Parent.Max.Y));
	return AxisBox2D(
		Point2D(x.Min, y.Min),
		Point2D(x.Max, y.Max)
	);
}
