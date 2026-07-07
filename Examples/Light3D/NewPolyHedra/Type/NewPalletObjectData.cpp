#include "NewPalletObjectData.hpp"
#include "ObjectManager.hpp"
#include "../PalletManager.hpp"



template<
	typename TypeData
>
NewPolyHedra_Type_PalletObjectData<TypeData> * sNewPalletObjectData(NewPolyHedra_Pallet * pallet)
{
	if (NewPolyHedra_Type_Data_ObjectManager<TypeData>::Current == nullptr) { return nullptr; }
	return (NewPolyHedra_Type_PalletObjectData<TypeData> *)NewPolyHedra_Type_Data_ObjectManager<TypeData>::Current -> NewPalletObjectData(pallet);
}

template<
	typename TypeData
>
NewPolyHedra_Type_PalletObjectData<TypeData> * sNewPalletObjectData(PolyHedra * polyhedra)
{
	if (NewPolyHedra_PalletManager::Current == nullptr) { return nullptr; }
	NewPolyHedra_Pallet * pallet = NewPolyHedra_PalletManager::Current -> FindMakePallet(polyhedra);
	return sNewPalletObjectData<TypeData>(pallet);
}
