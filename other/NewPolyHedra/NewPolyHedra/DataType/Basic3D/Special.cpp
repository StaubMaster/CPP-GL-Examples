#include "ObjectData.hpp"
#include "InstanceData.hpp"
#include "NewPolyHedra/Type/PalletObjectData.cpp"
#include "NewPolyHedra/Type/Object.cpp"



namespace NewPolyHedra
{
template struct Type_PalletObjectData<Basic3D::ObjectData>;
template struct Type_Object<Basic3D::ObjectData>;
};
