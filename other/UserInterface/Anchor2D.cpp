#include "Anchor2D.hpp"
#include "ValueType/Box/F1.hpp"
#include "ValueType/Box/F2.hpp"



Anchor2D::Anchor2D(
		VectorF2 & size,
		BoxF2 & dist,
		VectorF2 & normal_center
)
	: X(
		size.X,
		dist.Min.X,
		dist.Max.X,
		normal_center.X
	)
	, Y(
		size.Y,
		dist.Min.Y,
		dist.Max.Y,
		normal_center.Y
	)
{ }

void Anchor2D::ChangeBox(const BoxF2 & boxO, const BoxF2 & boxI)
{
	X.ChangeBox(boxO.Min.X, boxO.Max.X, boxI.Min.X, boxI.Max.X);
	Y.ChangeBox(boxO.Min.Y, boxO.Max.Y, boxI.Min.Y, boxI.Max.Y);
}
void Anchor2D::Update(const VectorF2 & size)
{
	X.Update(size.X);
	Y.Update(size.Y);
}
