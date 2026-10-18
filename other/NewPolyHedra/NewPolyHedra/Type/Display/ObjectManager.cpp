#include "NewPolyHedra/Type/Display/ObjectManager.hpp"
#include "NewPolyHedra/Type/Display/Object.hpp"



template<typename LogicalData> NewPolyHedra::DataDisplayObjectManager<LogicalData> * NewPolyHedra::DataDisplayObjectManager<LogicalData>::Current = nullptr;

template<typename LogicalData> NewPolyHedra::BaseDisplayObject * NewPolyHedra::DataDisplayObjectManager<LogicalData>::sFind(Pallet * pallet)
{
	if (Current == nullptr) { return nullptr; }
	return Current -> Find(pallet);
}
template<typename LogicalData> NewPolyHedra::BaseDisplayObject * NewPolyHedra::DataDisplayObjectManager<LogicalData>::sTake(Pallet * pallet)
{
	if (Current == nullptr) { return nullptr; }
	return Current -> Take(pallet);
}

template<typename LogicalData> NewPolyHedra::DataDisplayObjectManager<LogicalData>::~DataDisplayObjectManager()
{
	Current = nullptr;
}
template<typename LogicalData> NewPolyHedra::DataDisplayObjectManager<LogicalData>::DataDisplayObjectManager()
{
	Current = this;
}



template<typename LogicalData, typename DisplayData> NewPolyHedra::BaseDisplayObject * NewPolyHedra::TypeDisplayObjectManager<LogicalData, DisplayData>::NewBase(Pallet & pallet)
{
	return new TypeDisplayObject<LogicalData, DisplayData>(pallet);
}
