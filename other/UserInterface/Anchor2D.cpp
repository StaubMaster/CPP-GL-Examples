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

void Anchor2D::UpdateO(const BoxF2 & boxO)
{
	X.UpdateO(BoxF1(boxO.Min.X, boxO.Max.X));
	Y.UpdateO(BoxF1(boxO.Min.Y, boxO.Max.Y));
}
void Anchor2D::UpdateO(const BoxF2 & boxO, const BoxF2 & boxI)
{
	X.UpdateO(BoxF1(boxO.Min.X, boxO.Max.X), BoxF1(boxI.Min.X, boxI.Max.X));
	Y.UpdateO(BoxF1(boxO.Min.Y, boxO.Max.Y), BoxF1(boxI.Min.Y, boxI.Max.Y));
}

BoxF2 Anchor2D::ToInnerBox(const BoxF2 & boxO) const
{
	BoxF1 x = X.ToInnerBox(BoxF1(boxO.Min.X, boxO.Max.X));
	BoxF1 y = Y.ToInnerBox(BoxF1(boxO.Min.Y, boxO.Max.Y));
	return BoxF2(
		VectorF2(x.Min, y.Min),
		VectorF2(x.Max, y.Max)
	);
}
