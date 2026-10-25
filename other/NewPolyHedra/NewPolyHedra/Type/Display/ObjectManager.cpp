#include "NewPolyHedra/Type/Display/ObjectManager.hpp"
#include "NewPolyHedra/Type/Display/Object.hpp"



template<typename LogicalData> NewPolyHedra::DataDisplayObjectManager<LogicalData> * NewPolyHedra::DataDisplayObjectManager<LogicalData>::Current = nullptr;

template<typename LogicalData> NewPolyHedra::DataDisplayObject<LogicalData> * NewPolyHedra::DataDisplayObjectManager<LogicalData>::sFind(Pallet & pallet)
{
	if (Current == nullptr) { return nullptr; }
	return (Current -> Find(pallet));
}
template<typename LogicalData> NewPolyHedra::DataDisplayObject<LogicalData> * NewPolyHedra::DataDisplayObjectManager<LogicalData>::sTake(Pallet & pallet)
{
	if (Current == nullptr) { return nullptr; }
	return &(Current -> Take(pallet));
}



template<typename LogicalData> NewPolyHedra::DataDisplayObjectManager<LogicalData>::~DataDisplayObjectManager()
{
	Current = nullptr;
}
template<typename LogicalData> NewPolyHedra::DataDisplayObjectManager<LogicalData>::DataDisplayObjectManager()
{
	Current = this;
}





#include "Generics/Loop.hpp"

template<typename LogicalData, typename DisplayData> NewPolyHedra::TypeDisplayObjectManager<LogicalData, DisplayData>::~TypeDisplayObjectManager()
{
	Container::Loop::Delete(Objects);
}

template<typename LogicalData, typename DisplayData> unsigned int NewPolyHedra::TypeDisplayObjectManager<LogicalData, DisplayData>::Count() const
{
	return Objects.Count();
}



template<typename LogicalData, typename DisplayData> NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData> * NewPolyHedra::TypeDisplayObjectManager<LogicalData, DisplayData>::Find(const NewPolyHedra::Pallet & pallet) const
{
	return Container::Loop::Find(Objects, &NewPolyHedra::BaseDisplayObject::Equals, &pallet);
}
template<typename LogicalData, typename DisplayData> NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData> & NewPolyHedra::TypeDisplayObjectManager<LogicalData, DisplayData>::Make(NewPolyHedra::Pallet & pallet)
{
	NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData> * manager = new TypeDisplayObject<LogicalData, DisplayData>(pallet);

	manager -> GraphicsCreate();
	manager -> GraphicsInitFull(this -> BufferFullMainLayout, this -> BufferFullInstLayout);
	manager -> GraphicsInitWire(this -> BufferWireMainLayout, this -> BufferWireInstLayout);
	VertexArray::Base::BindNone();

	Objects.Insert(manager);
	return *manager;
}
template<typename LogicalData, typename DisplayData> NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData> & NewPolyHedra::TypeDisplayObjectManager<LogicalData, DisplayData>::Take(NewPolyHedra::Pallet & pallet)
{
	NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData> * manager = Find(pallet);
	if (manager != nullptr)
	{
		return *manager;
	}
	return Make(pallet);
}



/*template<typename LogicalData, typename DisplayData> NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData> * NewPolyHedra::TypeDisplayObjectManager<LogicalData, DisplayData>::Find(const Pallet * pallet) const
{
	if (pallet == nullptr) { return nullptr; }
	return Find(*pallet);
}*/
/*template<typename LogicalData, typename DisplayData> NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData> * NewPolyHedra::TypeDisplayObjectManager<LogicalData, DisplayData>::Make(Pallet * pallet)
{
	if (pallet == nullptr) { return nullptr; }
	return &Make(*pallet);
}*/
/*template<typename LogicalData, typename DisplayData> NewPolyHedra::TypeDisplayObject<LogicalData, DisplayData> * NewPolyHedra::TypeDisplayObjectManager<LogicalData, DisplayData>::Take(Pallet * pallet)
{
	if (pallet == nullptr) { return nullptr; }
	return &Take(*pallet);
}*/



template<typename LogicalData, typename DisplayData> unsigned int NewPolyHedra::TypeDisplayObjectManager<LogicalData, DisplayData>::InstancesFullCount() const
{
	return Container::Loop::SumUInt32(Objects, &NewPolyHedra::BaseDisplayObject::InstancesFullCount);
}
template<typename LogicalData, typename DisplayData> unsigned int NewPolyHedra::TypeDisplayObjectManager<LogicalData, DisplayData>::InstancesWireCount() const
{
	return Container::Loop::SumUInt32(Objects, &NewPolyHedra::BaseDisplayObject::InstancesWireCount);
}

template<typename LogicalData, typename DisplayData> void NewPolyHedra::TypeDisplayObjectManager<LogicalData, DisplayData>::InstancesClear()
{
	Container::Loop::Invoke(Objects, &NewPolyHedra::BaseDisplayObject::InstancesFullClear);
	Container::Loop::Invoke(Objects, &NewPolyHedra::BaseDisplayObject::InstancesWireClear);
}

template<typename LogicalData, typename DisplayData> void NewPolyHedra::TypeDisplayObjectManager<LogicalData, DisplayData>::GraphicsCreate()
{
	this -> ShaderFull.Create();
	this -> ShaderWire.Create();
	Container::Loop::Invoke(Objects, &NewPolyHedra::BaseDisplayObject::GraphicsCreate);
}
template<typename LogicalData, typename DisplayData> void NewPolyHedra::TypeDisplayObjectManager<LogicalData, DisplayData>::GraphicsDelete()
{
	this -> ShaderFull.Delete();
	this -> ShaderWire.Delete();
	Container::Loop::Invoke(Objects, &NewPolyHedra::BaseDisplayObject::GraphicsDelete);
}
template<typename LogicalData, typename DisplayData> void NewPolyHedra::TypeDisplayObjectManager<LogicalData, DisplayData>::GraphicsDrawFull()
{
	this -> ShaderFull.Bind();
	Container::Loop::Invoke(Objects, &NewPolyHedra::BaseDisplayObject::GraphicsDrawFull);
	VertexArray::Base::BindNone();
}
template<typename LogicalData, typename DisplayData> void NewPolyHedra::TypeDisplayObjectManager<LogicalData, DisplayData>::GraphicsDrawWire()
{
	this -> ShaderWire.Bind();
	Container::Loop::Invoke(Objects, &NewPolyHedra::BaseDisplayObject::GraphicsDrawWire);
	VertexArray::Base::BindNone();
}
