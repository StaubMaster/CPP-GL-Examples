#include "NewPolyHedra/Type/Display/Data.hpp"




template<typename TypeData, typename TypeInstanceData> NewPolyHedra::TypeDisplayData<TypeData, TypeInstanceData>::TypeDisplayData(Pallet & pallet)
	: BaseDisplayData(pallet)
{ }



template<typename TypeData, typename TypeInstanceData> unsigned int NewPolyHedra::TypeDisplayData<TypeData, TypeInstanceData>::InstancesFullCount() const
{
	return InstancesFullData.Count();
}
template<typename TypeData, typename TypeInstanceData> unsigned int NewPolyHedra::TypeDisplayData<TypeData, TypeInstanceData>::InstancesWireCount() const
{
	return InstancesWireData.Count();
}

template<typename TypeData, typename TypeInstanceData> void NewPolyHedra::TypeDisplayData<TypeData, TypeInstanceData>::InstancesFullClear()
{
	InstancesFullData.Clear();
}
template<typename TypeData, typename TypeInstanceData> void NewPolyHedra::TypeDisplayData<TypeData, TypeInstanceData>::InstancesWireClear()
{
	InstancesWireData.Clear();
}

template<typename TypeData, typename TypeInstanceData> void NewPolyHedra::TypeDisplayData<TypeData, TypeInstanceData>::InstancesFullPut(const void * data)
{
	InstancesFullPut(*((const TypeData *)data));
}
template<typename TypeData, typename TypeInstanceData> void NewPolyHedra::TypeDisplayData<TypeData, TypeInstanceData>::InstancesWirePut(const void * data)
{
	InstancesWirePut(*((const TypeData *)data));
}

template<typename TypeData, typename TypeInstanceData> void NewPolyHedra::TypeDisplayData<TypeData, TypeInstanceData>::InstancesFullPut(const TypeData & data)
{
	InstancesFullPut(TypeInstanceData(data));
}
template<typename TypeData, typename TypeInstanceData> void NewPolyHedra::TypeDisplayData<TypeData, TypeInstanceData>::InstancesWirePut(const TypeData & data)
{
	InstancesWirePut(TypeInstanceData(data));
}

template<typename TypeData, typename TypeInstanceData> void NewPolyHedra::TypeDisplayData<TypeData, TypeInstanceData>::InstancesFullPut(const TypeInstanceData & data)
{
	InstancesFullData.Insert(data);
}
template<typename TypeData, typename TypeInstanceData> void NewPolyHedra::TypeDisplayData<TypeData, TypeInstanceData>::InstancesWirePut(const TypeInstanceData & data)
{
	InstancesWireData.Insert(data);
}

template<typename TypeData, typename TypeInstanceData> void NewPolyHedra::TypeDisplayData<TypeData, TypeInstanceData>::InstancesFullToBuffer()
{
	BufferFullInstance.DataFull(InstancesFullData.ToVoid());
	CountFull = InstancesFullData.Count();
}
template<typename TypeData, typename TypeInstanceData> void NewPolyHedra::TypeDisplayData<TypeData, TypeInstanceData>::InstancesWireToBuffer()
{
	BufferWireInstance.DataFull(InstancesWireData.ToVoid());
	CountWire = InstancesWireData.Count();
}
