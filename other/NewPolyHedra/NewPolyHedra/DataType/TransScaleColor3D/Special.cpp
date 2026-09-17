#include "ObjectData.hpp"
#include "NewPolyHedra/Type/PalletObjectData.cpp"
#include "NewPolyHedra/Type/Object.cpp"



namespace NewPolyHedra
{
template struct Type_PalletObjectData<TransScaleColor3D::ObjectData>;
template struct Type_Object<TransScaleColor3D::ObjectData>;
};
