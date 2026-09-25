#include "ObjectManager.hpp"



template<typename TypeData> NewPolyHedra::Type_Data_ObjectManager<TypeData> * NewPolyHedra::Type_Data_ObjectManager<TypeData>::Current = nullptr;

template<typename TypeData> NewPolyHedra::Type_Data_ObjectManager<TypeData>::~Type_Data_ObjectManager()
{
	Current = nullptr;
}
template<typename TypeData> NewPolyHedra::Type_Data_ObjectManager<TypeData>::Type_Data_ObjectManager()
{
	Current = this;
}





template<typename TypeData, typename TypeInstanceData> NewPolyHedra::PalletObjectManager * NewPolyHedra::Type_ObjectManager<TypeData, TypeInstanceData>::PalletObjectManagersNew()
{
	return new Type_PalletObjectManager<TypeData, TypeInstanceData>();
	//PalletObjectManager * manager = new Type_PalletObjectManager<TypeData, TypeInstanceData>();
	////manager -> BufferFullInstance.SizeOf = sizeof(TypeInstanceData);
	////manager -> BufferWireInstance.SizeOf = sizeof(TypeInstanceData);
	//return manager;
}
template<typename TypeData, typename TypeInstanceData> NewPolyHedra::PalletObjectData * NewPolyHedra::Type_ObjectManager<TypeData, TypeInstanceData>::PalletObjectDatasNew()
{
	return new Type_PalletObjectData<TypeData>();
}
