#include "NewPalletObjectData.hpp"
#include "ObjectManager.hpp"
#include "../PalletManager.hpp"



namespace NewPolyHedra
{
template<
	typename TypeData
>
Type_PalletObjectData<TypeData> * sNewPalletObjectData(Pallet * pallet)
{
	if (Type_Data_ObjectManager<TypeData>::Current == nullptr) { return nullptr; }
	return (Type_PalletObjectData<TypeData> *)Type_Data_ObjectManager<TypeData>::Current -> NewPalletObjectData(pallet);
}

template<
	typename TypeData
>
Type_PalletObjectData<TypeData> * sNewPalletObjectData(PolyHedra * polyhedra)
{
	if (PalletManager::Current == nullptr) { return nullptr; }
	Pallet * pallet = PalletManager::Current -> FindMakePallet(polyhedra);
	return sNewPalletObjectData<TypeData>(pallet);
}
};
