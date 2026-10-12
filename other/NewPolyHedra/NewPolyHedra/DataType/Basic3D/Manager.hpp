#ifndef  NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_TYPE_MANAGER_HPP
# define NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_TYPE_MANAGER_HPP

# include "ObjectData.hpp"
# include "InstanceData.hpp"

# include "NewPolyHedra/Type/Manager.hpp"

namespace NewPolyHedra
{
namespace Basic3D
{
typedef ObjectData TypeData;
typedef InstanceData TypeInstanceData;
typedef TypeManager		<TypeData, TypeInstanceData> Manager;
};
};

#endif