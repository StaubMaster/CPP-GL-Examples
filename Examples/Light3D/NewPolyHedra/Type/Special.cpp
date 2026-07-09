#include "PalletObjectData.hpp"
#include "ObjectManager.hpp"
#include "../PalletManager.hpp"



// can this be done with a whole class ?
// like do this with the entire Object<> struct ?



template <typename TypeData>
NewPolyHedra::Type_PalletObjectData<TypeData> * NewPolyHedra::Type_PalletObjectData<TypeData>::Make(Pallet * pallet)
{
	if (Type_Data_ObjectManager<TypeData>::Current == nullptr) { return nullptr; }
	return (Type_PalletObjectData<TypeData> *)Type_Data_ObjectManager<TypeData>::Current -> NewPalletObjectData(pallet);
}

template <typename TypeData>
NewPolyHedra::Type_PalletObjectData<TypeData> * NewPolyHedra::Type_PalletObjectData<TypeData>::Make(PolyHedra * polyhedra)
{
	if (PalletManager::Current == nullptr) { return nullptr; }
	Pallet * pallet = PalletManager::Current -> FindMakePallet(polyhedra);
	return Type_PalletObjectData<TypeData>::Make(pallet);
}
