#include "NewPolyHedra/Type/Manager.hpp"
#include "NewPolyHedra/Type/Logical/ObjectManager.hpp"
#include "NewPolyHedra/Type/Display/ObjectManager.hpp"



/*template<typename LogicalData> NewPolyHedra::DataManager<LogicalData>::~DataManager()
{
	if (IsCurrent()) { ClearCurrent(); }
}*/
/*template<typename LogicalData> NewPolyHedra::DataManager<LogicalData>::DataManager()
{
	if (!CheckCurrent()) { MakeCurrent(); }
}*/

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



//template<typename LogicalData> NewPolyHedra::DataManager<LogicalData> * NewPolyHedra::DataManager<LogicalData>::Current_ = nullptr;
//template<typename LogicalData> NewPolyHedra::DataManager<LogicalData> & NewPolyHedra::DataManager<LogicalData>::Current() { return *Current_; }
//template<typename LogicalData> bool NewPolyHedra::DataManager<LogicalData>::CheckCurrent() { return (Current_ != nullptr); }
//template<typename LogicalData> void NewPolyHedra::DataManager<LogicalData>::ClearCurrent() { Current_ = nullptr; }
//template<typename LogicalData> bool NewPolyHedra::DataManager<LogicalData>::IsCurrent() const { return (Current_ == this); }
//template<typename LogicalData> void NewPolyHedra::DataManager<LogicalData>::MakeCurrent() { Current_ = this; }







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

template<typename LogicalData, typename DisplayData> NewPolyHedra::TypeManager<LogicalData, DisplayData>::~TypeManager()
{
	if (IsCurrent()) { ClearCurrent(); }
}
template<typename LogicalData, typename DisplayData> NewPolyHedra::TypeManager<LogicalData, DisplayData>::TypeManager()
{
	if (!CheckCurrent()) { MakeCurrent(); }
}



template<typename LogicalData, typename DisplayData> NewPolyHedra::TypeManager<LogicalData, DisplayData> * NewPolyHedra::TypeManager<LogicalData, DisplayData>::Current_ = nullptr;
template<typename LogicalData, typename DisplayData> NewPolyHedra::TypeManager<LogicalData, DisplayData> & NewPolyHedra::TypeManager<LogicalData, DisplayData>::Current() { return *Current_; }
template<typename LogicalData, typename DisplayData> bool NewPolyHedra::TypeManager<LogicalData, DisplayData>::CheckCurrent() { return (Current_ != nullptr); }
template<typename LogicalData, typename DisplayData> void NewPolyHedra::TypeManager<LogicalData, DisplayData>::ClearCurrent() { Current_ = nullptr; }
template<typename LogicalData, typename DisplayData> bool NewPolyHedra::TypeManager<LogicalData, DisplayData>::IsCurrent() const { return (Current_ == this); }
template<typename LogicalData, typename DisplayData> void NewPolyHedra::TypeManager<LogicalData, DisplayData>::MakeCurrent() { Current_ = this; }
