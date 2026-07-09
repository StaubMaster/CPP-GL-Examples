#include "../../Type/Special.cpp"
#include "../../Type/Special/Object.cpp"
#include "ObjectData.hpp"



namespace NewPolyHedra
{
template Type_PalletObjectData<TransScaleColor3D::ObjectData> * Type_PalletObjectData<TransScaleColor3D::ObjectData>::Make(Pallet * pallet);
template Type_PalletObjectData<TransScaleColor3D::ObjectData> * Type_PalletObjectData<TransScaleColor3D::ObjectData>::Make(PolyHedra * polyhedra);

template struct Type_Object<TransScaleColor3D::ObjectData>;
};
