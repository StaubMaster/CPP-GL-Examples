#ifndef  AXIS_3D_FUNCS_HPP
# define AXIS_3D_FUNCS_HPP

# include "Types.hpp"

struct VectorI3;
struct VectorF3;

namespace Axis3D
{
	Abs		RelToAbs(const Rel & axis);

	VectorI3	ToVectorI(const Rel & axis);
	VectorF3	ToVectorF(const Rel & axis);
};

#endif