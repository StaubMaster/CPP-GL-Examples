#ifndef  NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_OBJECT_HPP
# define NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_OBJECT_HPP

# include "NewPolyHedra/Type/Object.hpp"

# include "Special/Basic3D/Logical/Data.hpp"

namespace NewPolyHedra
{
namespace Basic3D
{
struct LogicalData;
typedef TypeObject<LogicalData> Object;
};
};

#endif