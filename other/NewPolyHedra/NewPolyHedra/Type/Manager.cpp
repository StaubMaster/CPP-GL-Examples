#include "NewPolyHedra/Type/Manager.hpp"
#include "NewPolyHedra/Type/Logical/ObjectManager.hpp"
#include "NewPolyHedra/Type/Display/ObjectManager.hpp"



template<typename LogicalData> NewPolyHedra::DataManager<LogicalData> * NewPolyHedra::DataManager<LogicalData>::Current = nullptr;

template<typename LogicalData> NewPolyHedra::DataManager<LogicalData>::~DataManager()
{
	Current = nullptr;
}
template<typename LogicalData> NewPolyHedra::DataManager<LogicalData>::DataManager()
{
	Current = this;
}

template<typename LogicalData> NewPolyHedra::BaseLogicalObjectManager & NewPolyHedra::DataManager<LogicalData>::LogicalBase()
{
	return LogicalType;
}
template<typename LogicalData> const NewPolyHedra::BaseLogicalObjectManager & NewPolyHedra::DataManager<LogicalData>::LogicalBase() const
{
	return LogicalType;
}





template<typename LogicalData, typename TypeInstanceData> NewPolyHedra::BaseDisplayObjectManager & NewPolyHedra::TypeManager<LogicalData, TypeInstanceData>::DisplayBase()
{
	return DisplayType;
}
template<typename LogicalData, typename TypeInstanceData> const NewPolyHedra::BaseDisplayObjectManager & NewPolyHedra::TypeManager<LogicalData, TypeInstanceData>::DisplayBase() const
{
	return DisplayType;
}
