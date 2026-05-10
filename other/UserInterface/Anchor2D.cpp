#include "Anchor2D.hpp"
#include "ValueType/Box/F1.hpp"
#include "ValueType/Box/F2.hpp"



Anchor2D::Anchor2D(Anchor1D x, Anchor1D y) :
	X(x),
	Y(y)
{ }

BoxF2 Anchor2D::Calculate(BoxF2 Parent)
{
	BoxF1 x = X.Calculate(BoxF1(Parent.Min.X, Parent.Max.X));
	BoxF1 y = Y.Calculate(BoxF1(Parent.Min.Y, Parent.Max.Y));
	return BoxF2(
		VectorF2(x.Min, y.Min),
		VectorF2(x.Max, y.Max)
	);
}
