#ifndef  NEW_POLYHEDRA_TEST_TYPE_TRANS_SCALE_COLOR_3D_INSTANCE_DATA_HPP
# define NEW_POLYHEDRA_TEST_TYPE_TRANS_SCALE_COLOR_3D_INSTANCE_DATA_HPP

# include "ValueType/Color/F4.hpp"
# include "ValueType/Matrix/4x4.hpp"

namespace TransScaleColor3D
{
struct InstanceData
{
	Matrix4x4	Trans;
	Matrix4x4	Normal;
	float		Scale;
	ColorF4		Color;
};
};

#endif