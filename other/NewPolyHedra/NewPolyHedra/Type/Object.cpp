#include "NewPolyHedra/Type/Object.hpp"

#include "NewPolyHedra/Type/Logical/Data.hpp"



template<typename TypeData> bool NewPolyHedra::Type_Object<TypeData>::Is() const
{
	return (ObjectData != nullptr);
}



template<typename TypeData> TypeData & NewPolyHedra::Type_Object<TypeData>::Data()
{
	return (ObjectData -> Data);
}
template<typename TypeData> const TypeData & NewPolyHedra::Type_Object<TypeData>::Data() const
{
	return (ObjectData -> Data);
}



template<typename TypeData> bool NewPolyHedra::Type_Object<TypeData>::VisibleFull() const
{
	return ObjectData -> VisibleFull();
}
template<typename TypeData> void NewPolyHedra::Type_Object<TypeData>::ShowFull()
{
	ObjectData -> ShowFull();
}
template<typename TypeData> void NewPolyHedra::Type_Object<TypeData>::HideFull()
{
	ObjectData -> HideFull();
}

template<typename TypeData> bool NewPolyHedra::Type_Object<TypeData>::VisibleWire() const
{
	return ObjectData -> VisibleWire();
}
template<typename TypeData> void NewPolyHedra::Type_Object<TypeData>::ShowWire()
{
	ObjectData -> ShowWire();
}
template<typename TypeData> void NewPolyHedra::Type_Object<TypeData>::HideWire()
{
	ObjectData -> HideWire();
}



template<typename TypeData> NewPolyHedra::BaseDisplayData * NewPolyHedra::Type_Object<TypeData>::Manager()
{
	return (ObjectData -> Graphics);
}
template<typename TypeData> const NewPolyHedra::BaseDisplayData * NewPolyHedra::Type_Object<TypeData>::Manager() const
{
	return (ObjectData -> Graphics);
}



template<typename TypeData> NewPolyHedra::Type_Object<TypeData>::~Type_Object()
{
	if (ObjectData != nullptr)
	{
		ObjectData -> Remove = true;
	}
}

template<typename TypeData> NewPolyHedra::Type_Object<TypeData>::Type_Object(Pallet * pallet)
	: ObjectData(TypeLogicalData<TypeData>::New(pallet))
{ }
template<typename TypeData> NewPolyHedra::Type_Object<TypeData>::Type_Object(PolyHedra * polyhedra)
	: ObjectData(TypeLogicalData<TypeData>::New(PalletManager::sTake(polyhedra)))
{ }



template<typename TypeData> void NewPolyHedra::Type_Object<TypeData>::Delete()
{
	if (ObjectData == nullptr) { return; }
	ObjectData -> Remove = true;
	ObjectData = nullptr;
}
template<typename TypeData> void NewPolyHedra::Type_Object<TypeData>::Create(Pallet * pallet)
{
	if (ObjectData != nullptr) { return; }
	ObjectData = TypeLogicalData<TypeData>::New(pallet);
}
template<typename TypeData> void NewPolyHedra::Type_Object<TypeData>::Create(PolyHedra * polyhedra)
{
	if (ObjectData != nullptr) { return; }
	ObjectData = TypeLogicalData<TypeData>::New(PalletManager::sTake(polyhedra));
}
