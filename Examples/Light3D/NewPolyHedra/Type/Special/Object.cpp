#include "../Object.hpp"
#include "../PalletObjectData.hpp"



template <typename TypeData> bool NewPolyHedra::Type_Object<TypeData>::Is() const
{
	return (PalletObjectData != nullptr);
}



template <typename TypeData> TypeData & NewPolyHedra::Type_Object<TypeData>::Data()
{
	return (PalletObjectData -> Data);
}
template <typename TypeData> const TypeData & NewPolyHedra::Type_Object<TypeData>::Data() const
{
	return (PalletObjectData -> Data);
}



template <typename TypeData> void NewPolyHedra::Type_Object<TypeData>::ShowFull()
{
	PalletObjectData -> ShowFull();
}
template <typename TypeData> void NewPolyHedra::Type_Object<TypeData>::HideFull()
{
	PalletObjectData -> HideFull();
}
template <typename TypeData> bool NewPolyHedra::Type_Object<TypeData>::VisibleFull() const
{
	return PalletObjectData -> VisibleFull();
}

template <typename TypeData> void NewPolyHedra::Type_Object<TypeData>::ShowWire()
{
	PalletObjectData -> ShowWire();
}
template <typename TypeData> void NewPolyHedra::Type_Object<TypeData>::HideWire()
{
	PalletObjectData -> HideWire();
}
template <typename TypeData> bool NewPolyHedra::Type_Object<TypeData>::VisibleWire() const
{
	return PalletObjectData -> VisibleWire();
}



template <typename TypeData> NewPolyHedra::PalletObjectManager * NewPolyHedra::Type_Object<TypeData>::Manager()
{
	return (PalletObjectData -> Manager);
}
template <typename TypeData> const NewPolyHedra::PalletObjectManager * NewPolyHedra::Type_Object<TypeData>::Manager() const
{
	return (PalletObjectData -> Manager);
}



template <typename TypeData> NewPolyHedra::Type_Object<TypeData>::~Type_Object()
{
	PalletObjectData -> Remove = true;
	/*if (PalletObjectData != nullptr)
	{
		if (!PalletObjectData -> Remove)
		{
			PalletObjectData -> Remove = true;
		}
		else
		{
			delete PalletObjectData;
		}
	}*/
}
template <typename TypeData> NewPolyHedra::Type_Object<TypeData>::Type_Object()
	: PalletObjectData(nullptr)
{ }
template <typename TypeData> NewPolyHedra::Type_Object<TypeData>::Type_Object(Pallet * pallet)
	: PalletObjectData(Type_PalletObjectData<TypeData>::Make(pallet))
{ }
template <typename TypeData> NewPolyHedra::Type_Object<TypeData>::Type_Object(PolyHedra * polyhedra)
	: PalletObjectData(Type_PalletObjectData<TypeData>::Make(polyhedra))
{ }



template <typename TypeData> void NewPolyHedra::Type_Object<TypeData>::Delete()
{
	if (PalletObjectData == nullptr) { return; }
	PalletObjectData -> Remove = true;
	PalletObjectData = nullptr;
}
template <typename TypeData> void NewPolyHedra::Type_Object<TypeData>::Create(Pallet * pallet)
{
	if (PalletObjectData != nullptr) { return; }
	PalletObjectData = Type_PalletObjectData<TypeData>::Make(pallet);
}
template <typename TypeData> void NewPolyHedra::Type_Object<TypeData>::Create(PolyHedra * polyhedra)
{
	if (PalletObjectData != nullptr) { return; }
	PalletObjectData = Type_PalletObjectData<TypeData>::Make(polyhedra);
}
