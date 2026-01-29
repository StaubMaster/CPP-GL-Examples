#ifndef  SPLINE_NODE_3D_HPP
# define SPLINE_NODE_3D_HPP

# include "ValueType/Point3D.hpp"

struct SplineNode3D
{
	Point3D	Pos;
	Point3D	Dir;

	SplineNode3D();
	SplineNode3D(Point3D pos, Point3D dir);
};

#endif