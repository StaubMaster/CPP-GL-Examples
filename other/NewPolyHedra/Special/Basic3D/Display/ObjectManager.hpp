#ifndef  NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_DISPLAY_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_DISPLAY_OBJECT_MANAGER_HPP

# include "NewPolyHedra/Type/Display/ObjectManager.hpp"

namespace NewPolyHedra
{
namespace Basic3D
{
struct LogicalData;
struct DisplayData;
typedef NewPolyHedra::TypeDisplayObjectManager<LogicalData, DisplayData> DisplayObjectManager;
};
};

#endif