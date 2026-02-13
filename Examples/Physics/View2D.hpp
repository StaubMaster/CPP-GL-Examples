#ifndef  VIEW_2D_HPP
# define VIEW_2D_HPP

# include "ValueType/Point2D.hpp"

struct Point3D;

struct View2D
{
	Point2D	Pos;
	float	Scale;

	View2D();
	~View2D();

	View2D(const View2D & other);
	View2D & operator=(const View2D & other);

	static View2D Default();

	void Transform(Point2D trans, float timeDelta);
};

#endif