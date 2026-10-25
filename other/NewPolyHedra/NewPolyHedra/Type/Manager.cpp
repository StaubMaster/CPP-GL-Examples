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

template<typename LogicalData> NewPolyHedra::TypeLogicalObjectManager<LogicalData> & NewPolyHedra::DataManager<LogicalData>::LogicalManager()
{
	return _LogicalManager;
}
template<typename LogicalData> const NewPolyHedra::TypeLogicalObjectManager<LogicalData> & NewPolyHedra::DataManager<LogicalData>::LogicalManager() const
{
	return _LogicalManager;
}
/*template<typename LogicalData> NewPolyHedra::TypeLogicalObject<LogicalData> * NewPolyHedra::DataManager<LogicalData>::NewLogicalObject(Pallet & pallet)
{
	return _LogicalManager.New(pallet);
}*/





template<typename LogicalData, typename DisplayData> NewPolyHedra::TypeDisplayObjectManager<LogicalData, DisplayData> & NewPolyHedra::TypeManager<LogicalData, DisplayData>::DisplayManager()
{
	return _DisplayManager;
}
template<typename LogicalData, typename DisplayData> const NewPolyHedra::TypeDisplayObjectManager<LogicalData, DisplayData> & NewPolyHedra::TypeManager<LogicalData, DisplayData>::DisplayManager() const
{
	return _DisplayManager;
}
template<typename LogicalData, typename DisplayData> NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData> * NewPolyHedra::TypeManager<LogicalData, DisplayData>::FindDisplayObject(const Pallet & pallet)
{
	return _DisplayManager.Find(pallet);
}
template<typename LogicalData, typename DisplayData> NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData> & NewPolyHedra::TypeManager<LogicalData, DisplayData>::TakeDisplayObject(Pallet & pallet)
{
	return _DisplayManager.Take(pallet);
}
