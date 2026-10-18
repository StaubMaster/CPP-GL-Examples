#ifndef  NEW_POLYHEDRA_DATA_TYPE_TRANS_SCALE_COLOR_3D_DISPLAY_OBJECT_HPP
# define NEW_POLYHEDRA_DATA_TYPE_TRANS_SCALE_COLOR_3D_DISPLAY_OBJECT_HPP

# include "NewPolyHedra/Type/Display/Object.hpp"

namespace TransScaleColor3D
{
struct LogicalData;
struct DisplayData;
typedef NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData> DisplayObject;
};

#endif