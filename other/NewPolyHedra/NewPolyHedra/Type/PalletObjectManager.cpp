#include "PalletObjectManager.hpp"



template<typename TypeData, typename TypeInstanceData> unsigned int NewPolyHedra::Type_PalletObjectManager<TypeData, TypeInstanceData>::InstancesFullCount() const
{
	return InstancesFullData.Count();
}
template<typename TypeData, typename TypeInstanceData> unsigned int NewPolyHedra::Type_PalletObjectManager<TypeData, TypeInstanceData>::InstancesWireCount() const
{
	return InstancesWireData.Count();
}

template<typename TypeData, typename TypeInstanceData> void NewPolyHedra::Type_PalletObjectManager<TypeData, TypeInstanceData>::InstancesFullClear()
{
	InstancesFullData.Clear();
}
template<typename TypeData, typename TypeInstanceData> void NewPolyHedra::Type_PalletObjectManager<TypeData, TypeInstanceData>::InstancesWireClear()
{
	InstancesWireData.Clear();
}

template<typename TypeData, typename TypeInstanceData> void NewPolyHedra::Type_PalletObjectManager<TypeData, TypeInstanceData>::InstancesFullPut(const void * data)
{
	InstancesFullPut(*((const TypeData *)data));
}
template<typename TypeData, typename TypeInstanceData> void NewPolyHedra::Type_PalletObjectManager<TypeData, TypeInstanceData>::InstancesWirePut(const void * data)
{
	InstancesWirePut(*((const TypeData *)data));
}

template<typename TypeData, typename TypeInstanceData> void NewPolyHedra::Type_PalletObjectManager<TypeData, TypeInstanceData>::InstancesFullPut(const TypeData & data)
{
	InstancesFullPut(TypeInstanceData(data));
}
template<typename TypeData, typename TypeInstanceData> void NewPolyHedra::Type_PalletObjectManager<TypeData, TypeInstanceData>::InstancesWirePut(const TypeData & data)
{
	InstancesWirePut(TypeInstanceData(data));
}

template<typename TypeData, typename TypeInstanceData> void NewPolyHedra::Type_PalletObjectManager<TypeData, TypeInstanceData>::InstancesFullPut(const TypeInstanceData & data)
{
	InstancesFullData.Insert(data);
}
template<typename TypeData, typename TypeInstanceData> void NewPolyHedra::Type_PalletObjectManager<TypeData, TypeInstanceData>::InstancesWirePut(const TypeInstanceData & data)
{
	InstancesWireData.Insert(data);
}

template<typename TypeData, typename TypeInstanceData> void NewPolyHedra::Type_PalletObjectManager<TypeData, TypeInstanceData>::InstancesFullToBuffer()
{
	BufferFullInstance.DataFull(InstancesFullData.ToVoid());
	CountFull = InstancesFullData.Count();
}
template<typename TypeData, typename TypeInstanceData> void NewPolyHedra::Type_PalletObjectManager<TypeData, TypeInstanceData>::InstancesWireToBuffer()
{
	BufferWireInstance.DataFull(InstancesWireData.ToVoid());
	CountWire = InstancesWireData.Count();
}
