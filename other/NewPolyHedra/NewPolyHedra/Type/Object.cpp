#include "NewPolyHedra/Type/Object.hpp"

#include "NewPolyHedra/Type/Logical/Object.hpp"
#include "NewPolyHedra/Type/Logical/ObjectManager.hpp"



template<typename LogicalData> bool NewPolyHedra::Type_Object<LogicalData>::Is() const
{
	return (ObjectData != nullptr);
}



template<typename LogicalData> LogicalData & NewPolyHedra::Type_Object<LogicalData>::Data()
{
	return (ObjectData -> Data);
}
template<typename LogicalData> const LogicalData & NewPolyHedra::Type_Object<LogicalData>::Data() const
{
	return (ObjectData -> Data);
}



template<typename LogicalData> NewPolyHedra::DataDisplayObject<LogicalData> * NewPolyHedra::Type_Object<LogicalData>::Graphics()
{
	return (ObjectData -> DisplayObject);
}
template<typename LogicalData> const NewPolyHedra::DataDisplayObject<LogicalData> * NewPolyHedra::Type_Object<LogicalData>::Graphics() const
{
	return (ObjectData -> DisplayObject);
}



template<typename LogicalData> bool NewPolyHedra::Type_Object<LogicalData>::VisibleFull() const
{
	return ObjectData -> VisibleFull();
}
template<typename LogicalData> void NewPolyHedra::Type_Object<LogicalData>::ShowFull()
{
	ObjectData -> ShowFull();
}
template<typename LogicalData> void NewPolyHedra::Type_Object<LogicalData>::HideFull()
{
	ObjectData -> HideFull();
}

template<typename LogicalData> bool NewPolyHedra::Type_Object<LogicalData>::VisibleWire() const
{
	return ObjectData -> VisibleWire();
}
template<typename LogicalData> void NewPolyHedra::Type_Object<LogicalData>::ShowWire()
{
	ObjectData -> ShowWire();
}
template<typename LogicalData> void NewPolyHedra::Type_Object<LogicalData>::HideWire()
{
	ObjectData -> HideWire();
}



template<typename LogicalData> NewPolyHedra::Type_Object<LogicalData>::~Type_Object()
{
	if (ObjectData != nullptr)
	{
		ObjectData -> Remove = true;
	}
}

template<typename LogicalData> NewPolyHedra::Type_Object<LogicalData>::Type_Object(Pallet * pallet)
	: ObjectData(TypeLogicalObjectManager<LogicalData>::sNewType(pallet))
{ }
template<typename LogicalData> NewPolyHedra::Type_Object<LogicalData>::Type_Object(PolyHedra * polyhedra)
	: ObjectData(TypeLogicalObjectManager<LogicalData>::sNewType(PalletManager::sTake(polyhedra)))
{ }



template<typename LogicalData> void NewPolyHedra::Type_Object<LogicalData>::Delete()
{
	if (ObjectData == nullptr) { return; }
	ObjectData -> Remove = true;
	ObjectData = nullptr;
}
template<typename LogicalData> void NewPolyHedra::Type_Object<LogicalData>::Create(Pallet * pallet)
{
	if (ObjectData != nullptr) { return; }
	ObjectData = TypeLogicalObjectManager<LogicalData>::sNewType(pallet);
}
template<typename LogicalData> void NewPolyHedra::Type_Object<LogicalData>::Create(PolyHedra * polyhedra)
{
	if (ObjectData != nullptr) { return; }
	ObjectData = TypeLogicalObjectManager<LogicalData>::sNewType(PalletManager::sTake(polyhedra));
}
