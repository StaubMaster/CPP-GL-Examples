#ifndef  NEW_POLYHEDRA_TEST_TYPE_TRANS_SCALE_COLOR_3D_OBJECT_DATA_HPP
# define NEW_POLYHEDRA_TEST_TYPE_TRANS_SCALE_COLOR_3D_OBJECT_DATA_HPP

# include "ValueType/Vector/F3.hpp"
# include "ValueType/Trans/3D.hpp"
# include "ValueType/Color/F4.hpp"

namespace TransScaleColor3D
{
struct ObjectData
{
	Trans3D		Trans;
	VectorF3	Scale;
	ColorF4		Color;
};
};

#endif