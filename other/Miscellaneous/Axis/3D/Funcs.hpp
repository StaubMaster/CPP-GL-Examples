#ifndef  AXIS_3D_FUNCS_HPP
# define AXIS_3D_FUNCS_HPP

# include "Types.hpp"

struct VectorF3;

namespace Axis3D
{
	Abs		RelToAbs(const Rel & axis);

	VectorF3	ToVector(const Rel & axis);
};

#endif