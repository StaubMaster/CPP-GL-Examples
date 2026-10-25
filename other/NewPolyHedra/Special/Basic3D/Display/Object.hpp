#ifndef  NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_DISPLAY_OBJECT_HPP
# define NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_DISPLAY_OBJECT_HPP

# include "NewPolyHedra/Type/Display/Object.hpp"

namespace NewPolyHedra
{
namespace Basic3D
{
struct LogicalData;
struct DisplayData;
typedef TypeDisplayObject<LogicalData, DisplayData> DisplayObject;
};
};

#endif