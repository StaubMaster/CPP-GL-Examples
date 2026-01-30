#include "Anchor2D.hpp"
#include "ValueType/AxisBox1D.hpp"
#include "ValueType/AxisBox2D.hpp"



Anchor2D::Anchor2D(Anchor1D x, Anchor1D y) :
	X(x),
	Y(y)
{ }

AxisBox2D Anchor2D::Calculate(AxisBox2D Parent)
{
	AxisBox1D x = X.Calculate(AxisBox1D(Parent.Min.X, Parent.Max.X));
	AxisBox1D y = Y.Calculate(AxisBox1D(Parent.Min.Y, Parent.Max.Y));
	return AxisBox2D(
		Point2D(x.Min, y.Min),
		Point2D(x.Max, y.Max)
	);
}
