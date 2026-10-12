#include "NewPolyHedra/Type/Manager.hpp"
#include "NewPolyHedra/Type/Logical/DataManager.hpp"
#include "NewPolyHedra/Type/Display/DataManager.hpp"



template<typename TypeData> NewPolyHedra::DataManager<TypeData> * NewPolyHedra::DataManager<TypeData>::Current = nullptr;

template<typename TypeData> NewPolyHedra::DataManager<TypeData>::~DataManager()
{
	Current = nullptr;
}
template<typename TypeData> NewPolyHedra::DataManager<TypeData>::DataManager()
{
	Current = this;
}

template<typename TypeData> NewPolyHedra::BaseLogicalDataManager & NewPolyHedra::DataManager<TypeData>::LogicalBase()
{
	return LogicalType;
}
template<typename TypeData> const NewPolyHedra::BaseLogicalDataManager & NewPolyHedra::DataManager<TypeData>::LogicalBase() const
{
	return LogicalType;
}





template<typename TypeData, typename TypeInstanceData> NewPolyHedra::BaseDisplayDataManager & NewPolyHedra::TypeManager<TypeData, TypeInstanceData>::DisplayBase()
{
	return DisplayType;
}
template<typename TypeData, typename TypeInstanceData> const NewPolyHedra::BaseDisplayDataManager & NewPolyHedra::TypeManager<TypeData, TypeInstanceData>::DisplayBase() const
{
	return DisplayType;
}
