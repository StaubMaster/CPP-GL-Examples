#include "NewPolyHedra/Type/Logical/DataManager.hpp"
#include "NewPolyHedra/Type/Logical/Data.hpp"

#include "NewPolyHedra/Type/Display/DataManager.hpp"

#include "NewPolyHedra/Pallet/Manager.hpp"



template<typename TypeData> NewPolyHedra::TypeLogicalDataManager<TypeData> * NewPolyHedra::TypeLogicalDataManager<TypeData>::Current = nullptr;

template<typename TypeData> NewPolyHedra::TypeLogicalData<TypeData> * NewPolyHedra::TypeLogicalDataManager<TypeData>::sNewType(Pallet * pallet)
{
	if (Current == nullptr) { return nullptr; }
	return Current -> NewType(pallet);
}

template<typename TypeData> NewPolyHedra::TypeLogicalDataManager<TypeData>::~TypeLogicalDataManager()
{
	Current = nullptr;
}
template<typename TypeData> NewPolyHedra::TypeLogicalDataManager<TypeData>::TypeLogicalDataManager()
{
	Current = this;
}



template<typename TypeData> NewPolyHedra::TypeLogicalData<TypeData> * NewPolyHedra::TypeLogicalDataManager<TypeData>::NewType(Pallet * pallet)
{
	if (pallet == nullptr) { return nullptr; }
	//if (DataDisplayDataManager<TypeData>::Current == nullptr) { return nullptr; }
	TypeLogicalData<TypeData> * object = new TypeLogicalData<TypeData>();
	//object -> Graphics = DataDisplayDataManager<TypeData>::Current -> FindMake(pallet);
	object -> Graphics = DataDisplayDataManager<TypeData>::sTake(pallet);
	this -> Datas.Insert(object);
	return object;
}
template<typename TypeData> NewPolyHedra::BaseLogicalData * NewPolyHedra::TypeLogicalDataManager<TypeData>::NewBase(Pallet * pallet)
{
	return NewType(pallet);
}
