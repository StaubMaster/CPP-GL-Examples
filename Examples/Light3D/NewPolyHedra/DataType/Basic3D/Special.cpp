#include "../../Type/Special.cpp"
#include "ObjectData.hpp"



namespace NewPolyHedra
{
template Type_PalletObjectData<Basic3D::ObjectData> * Type_PalletObjectData<Basic3D::ObjectData>::Make(Pallet * pallet);
template Type_PalletObjectData<Basic3D::ObjectData> * Type_PalletObjectData<Basic3D::ObjectData>::Make(PolyHedra * polyhedra);
};
