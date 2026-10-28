#ifndef  NEW_POLYHEDRA_USER_INTERFACE_DISPLAY_DATA_HPP
# define NEW_POLYHEDRA_USER_INTERFACE_DISPLAY_DATA_HPP

# include "ValueType/Vector/F2.hpp"
# include "ValueType/Matrix/3x3.hpp"

namespace NewPolyHedra
{
namespace UserInterface
{
struct LogicalData;
struct DisplayData
{
	VectorF2	Size;
	VectorF2	Pos;
	Matrix3x3	Rot;
	float		Scale = 1.0f;
	~DisplayData() = default;
	DisplayData() = default;
	DisplayData(const LogicalData & data);
};
};
};

#endif