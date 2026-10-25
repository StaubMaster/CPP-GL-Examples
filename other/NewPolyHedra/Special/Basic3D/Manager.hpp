#ifndef  NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_MANAGER_HPP
# define NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_MANAGER_HPP

# include "NewPolyHedra/Type/Manager.hpp"

namespace NewPolyHedra
{
namespace Basic3D
{
struct LogicalData;
struct DisplayData;
typedef TypeManager<LogicalData, DisplayData> Manager;
};
};

#endif