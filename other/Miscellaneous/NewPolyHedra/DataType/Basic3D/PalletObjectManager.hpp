#ifndef  NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_PALLET_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_DATA_TYPE_BASIC_3D_PALLET_OBJECT_MANAGER_HPP

# include "NewPolyHedra/Type/PalletObjectManager.hpp"
# include "ObjectData.hpp"
# include "InstanceData.hpp"

namespace NewPolyHedra
{
namespace Basic3D
{
typedef NewPolyHedra::Type_PalletObjectManager<NewPolyHedra::Basic3D::ObjectData, NewPolyHedra::Basic3D::InstanceData> PalletObjectManager;
};
};

#endif