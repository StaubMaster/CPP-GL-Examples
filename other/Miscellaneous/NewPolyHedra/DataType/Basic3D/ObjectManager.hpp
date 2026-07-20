#ifndef  NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_OBJECT_MANAGER_HPP

# include "NewPolyHedra/Type/ObjectManager.hpp"
# include "ObjectData.hpp"
# include "InstanceData.hpp"

namespace NewPolyHedra
{
namespace Basic3D
{
typedef Type_ObjectManager<ObjectData, InstanceData> ObjectManager;
};
};

#endif