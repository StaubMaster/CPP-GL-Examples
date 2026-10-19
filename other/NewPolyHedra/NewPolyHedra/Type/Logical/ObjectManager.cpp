#include "NewPolyHedra/Type/Logical/ObjectManager.hpp"
#include "NewPolyHedra/Type/Logical/Object.hpp"

#include "NewPolyHedra/Type/Display/ObjectManager.hpp"

#include "NewPolyHedra/Pallet/Manager.hpp"



template<typename LogicalData> NewPolyHedra::TypeLogicalObjectManager<LogicalData> * NewPolyHedra::TypeLogicalObjectManager<LogicalData>::Current = nullptr;

template<typename LogicalData> NewPolyHedra::TypeLogicalObject<LogicalData> * NewPolyHedra::TypeLogicalObjectManager<LogicalData>::sNewType(Pallet * pallet)
{
	if (Current == nullptr) { return nullptr; }
	return Current -> NewType(pallet);
}

template<typename LogicalData> NewPolyHedra::TypeLogicalObjectManager<LogicalData>::~TypeLogicalObjectManager()
{
	Current = nullptr;
}
template<typename LogicalData> NewPolyHedra::TypeLogicalObjectManager<LogicalData>::TypeLogicalObjectManager()
{
	Current = this;
}



template<typename LogicalData> NewPolyHedra::BaseLogicalObject * NewPolyHedra::TypeLogicalObjectManager<LogicalData>::NewBase(Pallet * pallet)
{
	return NewType(pallet);
}
template<typename LogicalData> NewPolyHedra::TypeLogicalObject<LogicalData> * NewPolyHedra::TypeLogicalObjectManager<LogicalData>::NewType(Pallet * pallet)
{
	if (pallet == nullptr) { return nullptr; }
	TypeLogicalObject<LogicalData> * object = new TypeLogicalObject<LogicalData>();
	object -> DisplayObject = (DataDisplayObject<LogicalData>*)DataDisplayObjectManager<LogicalData>::sTake(pallet); // sTakeType
	this -> Datas.Insert(object);
	return object;
}
