#ifndef  NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_DISPLAY_OBJECT_HPP
# define NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_DISPLAY_OBJECT_HPP

# include "NewPolyHedra/Type/Display/Object.hpp"

# include "Special/Basic3D/Logical/Data.hpp"
# include "Special/Basic3D/Display/Data.hpp"

namespace NewPolyHedra
{
namespace Basic3D
{
typedef TypeDisplayObject<LogicalData, DisplayData> DisplayObject;
};
};

#endif