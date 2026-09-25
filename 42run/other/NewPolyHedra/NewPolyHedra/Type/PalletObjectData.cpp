#include "PalletObjectData.hpp"
#include "ObjectManager.hpp"
#include "../PalletManager.hpp"



template<typename TypeData> const void * NewPolyHedra::Type_PalletObjectData<TypeData>::DataVoid() const
{
	return &Data;
}



template<typename TypeData> NewPolyHedra::Type_PalletObjectData<TypeData> * NewPolyHedra::Type_PalletObjectData<TypeData>::New(Pallet * pallet)
{
	if (Type_Data_ObjectManager<TypeData>::Current == nullptr) { return nullptr; }
	return (Type_PalletObjectData<TypeData> *)Type_Data_ObjectManager<TypeData>::Current -> PalletObjectDatasNew(pallet);
}

template<typename TypeData> NewPolyHedra::Type_PalletObjectData<TypeData> * NewPolyHedra::Type_PalletObjectData<TypeData>::New(PolyHedra * polyhedra)
{
	if (Type_Data_ObjectManager<TypeData>::Current == nullptr) { return nullptr; }
	return (Type_PalletObjectData<TypeData> *)Type_Data_ObjectManager<TypeData>::Current -> PalletObjectDatasNew(polyhedra);
}
