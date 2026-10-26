#ifndef  NEW_POLYHEDRA_USER_INTERFACE_MANAGER_HPP
# define NEW_POLYHEDRA_USER_INTERFACE_MANAGER_HPP

# include "NewPolyHedra/Type/Manager.hpp"

# include "NewPolyHedra/UserInterface/Logical/Data.hpp"
# include "NewPolyHedra/UserInterface/Display/Data.hpp"

namespace NewPolyHedra
{
namespace UserInterface
{
typedef TypeManager <LogicalData, DisplayData> Manager;
};
};

#endif