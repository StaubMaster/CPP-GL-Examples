#include "ObjectData.hpp"
#include "../../Type/PalletObjectData.cpp"
#include "../../Type/Object.cpp"



namespace NewPolyHedra
{
template struct Type_PalletObjectData<Basic3D::ObjectData>;
template struct Type_Object<Basic3D::ObjectData>;
};
