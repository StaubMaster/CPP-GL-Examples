#include "NewPolyHedra/Type/Object.hpp"

#include "NewPolyHedra/Type/Logical/Object.hpp"
#include "NewPolyHedra/Type/Logical/ObjectManager.hpp"



template<typename LogicalData> bool NewPolyHedra::TypeObject<LogicalData>::Is() const
{
	return (ObjectData != nullptr);
}



template<typename LogicalData> LogicalData & NewPolyHedra::TypeObject<LogicalData>::Data()
{
	return (ObjectData -> Data);
}
template<typename LogicalData> const LogicalData & NewPolyHedra::TypeObject<LogicalData>::Data() const
{
	return (ObjectData -> Data);
}



template<typename LogicalData> NewPolyHedra::DataDisplayObject<LogicalData> * NewPolyHedra::TypeObject<LogicalData>::Graphics()
{
	return (ObjectData -> DisplayObject);
}
template<typename LogicalData> const NewPolyHedra::DataDisplayObject<LogicalData> * NewPolyHedra::TypeObject<LogicalData>::Graphics() const
{
	return (ObjectData -> DisplayObject);
}



template<typename LogicalData> bool NewPolyHedra::TypeObject<LogicalData>::VisibleFull() const
{
	return ObjectData -> VisibleFull();
}
template<typename LogicalData> void NewPolyHedra::TypeObject<LogicalData>::ShowFull()
{
	ObjectData -> ShowFull();
}
template<typename LogicalData> void NewPolyHedra::TypeObject<LogicalData>::HideFull()
{
	ObjectData -> HideFull();
}

template<typename LogicalData> bool NewPolyHedra::TypeObject<LogicalData>::VisibleWire() const
{
	return ObjectData -> VisibleWire();
}
template<typename LogicalData> void NewPolyHedra::TypeObject<LogicalData>::ShowWire()
{
	ObjectData -> ShowWire();
}
template<typename LogicalData> void NewPolyHedra::TypeObject<LogicalData>::HideWire()
{
	ObjectData -> HideWire();
}



template<typename LogicalData> NewPolyHedra::TypeObject<LogicalData>::~TypeObject()
{
	if (ObjectData != nullptr)
	{
		ObjectData -> Remove = true;
	}
}

template<typename LogicalData> NewPolyHedra::TypeObject<LogicalData>::TypeObject(Pallet & pallet)
	: ObjectData(TypeLogicalObjectManager<LogicalData>::sNew(pallet))
{ }
template<typename LogicalData> NewPolyHedra::TypeObject<LogicalData>::TypeObject(PolyHedra & polyhedra)
	: ObjectData(TypeLogicalObjectManager<LogicalData>::sNew(PalletManager::sTake(polyhedra)))
{ }



template<typename LogicalData> void NewPolyHedra::TypeObject<LogicalData>::Delete()
{
	if (ObjectData == nullptr) { return; }
	ObjectData -> Remove = true;
	ObjectData = nullptr;
}
template<typename LogicalData> void NewPolyHedra::TypeObject<LogicalData>::Create(Pallet & pallet)
{
	if (ObjectData != nullptr) { return; }
	ObjectData = TypeLogicalObjectManager<LogicalData>::sNew(pallet);
}
template<typename LogicalData> void NewPolyHedra::TypeObject<LogicalData>::Create(PolyHedra & polyhedra)
{
	if (ObjectData != nullptr) { return; }
	ObjectData = TypeLogicalObjectManager<LogicalData>::sNew(PalletManager::sTake(polyhedra));
}
