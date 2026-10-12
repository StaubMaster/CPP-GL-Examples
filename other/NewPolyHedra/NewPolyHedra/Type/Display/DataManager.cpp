#include "NewPolyHedra/Type/Display/DataManager.hpp"
#include "NewPolyHedra/Type/Display/Data.hpp"



template<typename TypeData> NewPolyHedra::DataDisplayDataManager<TypeData> * NewPolyHedra::DataDisplayDataManager<TypeData>::Current = nullptr;

template<typename TypeData> NewPolyHedra::BaseDisplayData * NewPolyHedra::DataDisplayDataManager<TypeData>::sFind(Pallet * pallet)
{
	if (Current == nullptr) { return nullptr; }
	return Current -> Find(pallet);
}
template<typename TypeData> NewPolyHedra::BaseDisplayData * NewPolyHedra::DataDisplayDataManager<TypeData>::sTake(Pallet * pallet)
{
	if (Current == nullptr) { return nullptr; }
	return Current -> Take(pallet);
}

template<typename TypeData> NewPolyHedra::DataDisplayDataManager<TypeData>::~DataDisplayDataManager()
{
	Current = nullptr;
}
template<typename TypeData> NewPolyHedra::DataDisplayDataManager<TypeData>::DataDisplayDataManager()
{
	Current = this;
}



template<typename TypeData, typename TypeInstanceData> NewPolyHedra::BaseDisplayData * NewPolyHedra::TypeDisplayDataManager<TypeData, TypeInstanceData>::NewBase(Pallet & pallet)
{
	return new TypeDisplayData<TypeData, TypeInstanceData>(pallet);
}
