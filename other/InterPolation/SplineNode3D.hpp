#ifndef  SPLINE_NODE_3D_HPP
# define SPLINE_NODE_3D_HPP

# include "ValueType/VectorF3.hpp"

struct SplineNode3D
{
	VectorF3	Pos;
	VectorF3	Dir;

	SplineNode3D();
	SplineNode3D(VectorF3 pos, VectorF3 dir);
};

#endif