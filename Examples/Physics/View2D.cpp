#include "View2D.hpp"



View2D::View2D()
	: Pos()
	, Scale(0.0f)
{ }
View2D::~View2D()
{ }

View2D::View2D(const View2D & other)
	: Pos(other.Pos)
	, Scale(other.Scale)
{ }
View2D & View2D::operator=(const View2D & other)
{
	Pos = other.Pos;
	Scale = other.Scale;
	return *this;
}



View2D View2D::Default()
{
	View2D view;
	view.Scale = 10.0f;
	return view;
}



void View2D::Transform(Point2D trans, float timeDelta)
{
	Pos += trans * timeDelta;
}
