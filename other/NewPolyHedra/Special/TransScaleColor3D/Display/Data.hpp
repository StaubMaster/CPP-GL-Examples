#ifndef  NEW_POLYHEDRA_DATA_TYPE_TRANS_SCALE_COLOR_3D_DISPLAY_DATA_HPP
# define NEW_POLYHEDRA_DATA_TYPE_TRANS_SCALE_COLOR_3D_DISPLAY_DATA_HPP

# include "ValueType/Matrix/4x4.hpp"
# include "ValueType/Color/F4.hpp"

namespace TransScaleColor3D
{
struct LogicalData;
struct DisplayData
{
	Matrix4x4	Trans; // Scale should happen before everything else
	ColorF4		Color;
	~DisplayData() = default;
	DisplayData() = default;
	DisplayData(const LogicalData & data);
};
};

#endif