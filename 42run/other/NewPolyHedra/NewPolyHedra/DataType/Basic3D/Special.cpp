#include "ObjectData.hpp"
#include "InstanceData.hpp"

#include "NewPolyHedra/Type/ObjectManager.cpp"
#include "NewPolyHedra/Type/PalletObjectManager.cpp"
#include "NewPolyHedra/Type/PalletObjectData.cpp"
#include "NewPolyHedra/Type/Object.cpp"



namespace NewPolyHedra
{
typedef Basic3D::ObjectData TypeData;
typedef Basic3D::InstanceData TypeInstanceData;
template struct Type_Data_ObjectManager<TypeData>;
template struct Type_ObjectManager<TypeData, TypeInstanceData>;
template struct Type_PalletObjectManager<TypeData, TypeInstanceData>;
template struct Type_PalletObjectData<TypeData>;
template struct Type_Object<TypeData>;
};
