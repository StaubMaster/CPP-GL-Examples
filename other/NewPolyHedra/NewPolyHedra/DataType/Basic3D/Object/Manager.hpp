#ifndef  NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_PALLET_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_PALLET_OBJECT_MANAGER_HPP

# include "ObjectData.hpp"
# include "InstanceData.hpp"

# include "NewPolyHedra/Type/Graphics/Inst.hpp"

namespace NewPolyHedra
{
namespace Basic3D
{
typedef ObjectData TypeData;
typedef InstanceData TypeInstanceData;
typedef TypeGraphicsInst<TypeData, TypeInstanceData> GraphicsInst;
};
};

#endif