#ifndef  NEW_POLYHEDRA_USER_INTERFACE_LOGICAL_DATA_HPP
# define NEW_POLYHEDRA_USER_INTERFACE_LOGICAL_DATA_HPP

# include "ValueType/Vector/F2.hpp"
# include "ValueType/EulerAngle3D.hpp"

namespace NewPolyHedra
{
namespace UserInterface
{
struct LogicalData
{
	VectorF2		Size;
	VectorF2		Pos;
	EulerAngle3D	Rot;
	float			Scale = 1.0f;
};
};
};

#endif