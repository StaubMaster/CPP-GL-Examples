#ifndef  NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_DISPLAY_DATA_HPP
# define NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_DISPLAY_DATA_HPP

# include "ValueType/Matrix/4x4.hpp"

namespace NewPolyHedra
{
namespace Basic3D
{
struct LogicalData;
struct DisplayData
{
	Matrix4x4	Trans;
	Matrix4x4	Normal;
	~DisplayData() = default;
	DisplayData() = default;
	DisplayData(const LogicalData & data);
};
};
};

#endif