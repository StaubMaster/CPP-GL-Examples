#include "NewPolyHedra/Type/Display/Object.hpp"



template<typename LogicalData> NewPolyHedra::DataDisplayObject<LogicalData>::DataDisplayObject(Pallet & pallet)
	: BaseDisplayObject(pallet)
{ }



template<typename LogicalData, typename DisplayData> NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData>::TypeDisplayObject(Pallet & pallet)
	: DataDisplayObject<LogicalData>(pallet)
{ }



template<typename LogicalData, typename DisplayData> unsigned int NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData>::InstancesFullCount() const
{
	return InstancesFullData.Count();
}
template<typename LogicalData, typename DisplayData> unsigned int NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData>::InstancesWireCount() const
{
	return InstancesWireData.Count();
}

template<typename LogicalData, typename DisplayData> void NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData>::InstancesFullClear()
{
	InstancesFullData.Clear();
}
template<typename LogicalData, typename DisplayData> void NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData>::InstancesWireClear()
{
	InstancesWireData.Clear();
}

template<typename LogicalData, typename DisplayData> void NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData>::InstancesFullPut(const LogicalData & data)
{
	InstancesFullPut(DisplayData(data));
}
template<typename LogicalData, typename DisplayData> void NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData>::InstancesWirePut(const LogicalData & data)
{
	InstancesWirePut(DisplayData(data));
}

template<typename LogicalData, typename DisplayData> void NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData>::InstancesFullPut(const DisplayData & data)
{
	InstancesFullData.Insert(data);
}
template<typename LogicalData, typename DisplayData> void NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData>::InstancesWirePut(const DisplayData & data)
{
	InstancesWireData.Insert(data);
}

template<typename LogicalData, typename DisplayData> void NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData>::InstancesFullToBuffer()
{
	// why does this require "this"
	this -> BufferFullInstance.DataFull(InstancesFullData.ToVoid());
	this -> CountFull = InstancesFullData.Count();
}
template<typename LogicalData, typename DisplayData> void NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData>::InstancesWireToBuffer()
{
	// why does this require "this"
	this -> BufferWireInstance.DataFull(InstancesWireData.ToVoid());
	this -> CountWire = InstancesWireData.Count();
}
