#include "Anchor2D.hpp"
#include "ValueType/Box/F1.hpp"
#include "ValueType/Box/F2.hpp"



Anchor2D::Anchor2D(
		VectorF2 & size,
		BoxF2 & dist,
		BoxF2 & margin,
		BoxF2 & boarder,
		BoxF2 & padding,
		VectorF2 & normal_center
)
	: X(
		size.X,
		refBoxF1(dist.Min.X, dist.Max.X),
		refBoxF1(margin.Min.X, margin.Max.X),
		refBoxF1(boarder.Min.X, boarder.Max.X),
		refBoxF1(padding.Min.X, padding.Max.X),
		normal_center.X
	)
	, Y(
		size.Y,
		refBoxF1(dist.Min.Y, dist.Max.Y),
		refBoxF1(margin.Min.Y, margin.Max.Y),
		refBoxF1(boarder.Min.Y, boarder.Max.Y),
		refBoxF1(padding.Min.Y, padding.Max.Y),
		normal_center.Y
	)
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
void Anchor2D::Calculate(BoxF2 Parent, BoxF2 box)
{
	X.Calculate(BoxF1(Parent.Min.X, Parent.Max.X), BoxF1(box.Min.X, box.Max.X));
	Y.Calculate(BoxF1(Parent.Min.Y, Parent.Max.Y), BoxF1(box.Min.Y, box.Max.Y));
}
