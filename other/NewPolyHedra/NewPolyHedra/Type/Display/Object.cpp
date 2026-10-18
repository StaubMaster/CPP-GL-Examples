#include "NewPolyHedra/Type/Display/Object.hpp"




template<typename LogicalData, typename DisplayData> NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData>::TypeDisplayObject(Pallet & pallet)
	: BaseDisplayObject(pallet)
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

template<typename LogicalData, typename DisplayData> void NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData>::InstancesFullPut(const void * data)
{
	InstancesFullPut(*((const LogicalData *)data));
}
template<typename LogicalData, typename DisplayData> void NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData>::InstancesWirePut(const void * data)
{
	InstancesWirePut(*((const LogicalData *)data));
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
	BufferFullInstance.DataFull(InstancesFullData.ToVoid());
	CountFull = InstancesFullData.Count();
}
template<typename LogicalData, typename DisplayData> void NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData>::InstancesWireToBuffer()
{
	BufferWireInstance.DataFull(InstancesWireData.ToVoid());
	CountWire = InstancesWireData.Count();
}
