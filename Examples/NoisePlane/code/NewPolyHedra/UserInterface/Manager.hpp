#ifndef  NEW_POLYHEDRA_USER_INTERFACE_MANAGER_HPP
# define NEW_POLYHEDRA_USER_INTERFACE_MANAGER_HPP

# include "NewPolyHedra/Type/Manager.hpp"

namespace NewPolyHedra
{
namespace UserInterface
{
struct LogicalData;
struct DisplayData;
typedef TypeManager <LogicalData, DisplayData> Manager;
};
};

#endif