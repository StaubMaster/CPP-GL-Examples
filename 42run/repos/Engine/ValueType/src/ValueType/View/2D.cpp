#include "ValueType/View/2D.hpp"



View2D::~View2D() { }

View2D::View2D()
	: Trans()
	, Scale(0.0f)
{ }

View2D::View2D(const View2D & other)
	: Trans(other.Trans)
	, Scale(other.Scale)
{ }
View2D & View2D::operator=(const View2D & other)
{
	Trans = other.Trans;
	Scale = other.Scale;
	return *this;
}

View2D View2D::Default()
{
	View2D view;
	view.Scale = 1.0f;
	return view;
}

void View2D::Change(Trans2D change, float timeDelta)
{
	change.Pos *= timeDelta;
	change.Rot *= timeDelta;

	Trans.Pos += Trans.Rot.forward(change.Pos);
	Trans.Rot += change.Rot;
}



VectorF2 View2D::forward(VectorF2 p) const { return Trans.forward(p * Scale); }
VectorF2 View2D::reverse(VectorF2 p) const { return Trans.reverse(p) / Scale; }
