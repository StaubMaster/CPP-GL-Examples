#include "../../Type/NewPalletObjectData.cpp"
#include "ObjectData.hpp"



namespace NewPolyHedra
{
template Type_PalletObjectData<Basic3D::ObjectData> * sNewPalletObjectData(Pallet * pallet);
template Type_PalletObjectData<Basic3D::ObjectData> * sNewPalletObjectData(PolyHedra * polyhedra);
};
