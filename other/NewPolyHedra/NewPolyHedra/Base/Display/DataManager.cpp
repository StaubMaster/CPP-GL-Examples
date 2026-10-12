#include "NewPolyHedra/Base/Display/DataManager.hpp"
#include "NewPolyHedra/Base/Display/Data.hpp"

#include "NewPolyHedra/Pallet/Manager.hpp"

#include "Generics/Loop.hpp"
#include "Graphics/VertexArray/Base.hpp"



NewPolyHedra::BaseDisplayDataManager::~BaseDisplayDataManager()
{
	Container::Loop::Delete(s);
}

unsigned int NewPolyHedra::BaseDisplayDataManager::Count() const
{
	return s.Count();
}

NewPolyHedra::BaseDisplayData * NewPolyHedra::BaseDisplayDataManager::Find(NewPolyHedra::Pallet * pallet) const
{
	if (pallet == nullptr) { return nullptr; }
	return Container::Loop::Find(s, NewPolyHedra::BaseDisplayData::Equals, (const NewPolyHedra::Pallet *)pallet);
}
NewPolyHedra::BaseDisplayData * NewPolyHedra::BaseDisplayDataManager::Make(NewPolyHedra::Pallet * pallet)
{
	if (pallet == nullptr) { return nullptr; }
	BaseDisplayData * manager = NewBase(*pallet);

	manager -> GraphicsCreate();
	manager -> GraphicsInitFull(BufferFullLayout);
	manager -> GraphicsInitWire(BufferWireLayout);
	VertexArray::Base::BindNone();

	s.Insert(manager);
	return manager;
}
NewPolyHedra::BaseDisplayData * NewPolyHedra::BaseDisplayDataManager::Take(NewPolyHedra::Pallet * pallet)
{
	if (pallet == nullptr) { return nullptr; }
	NewPolyHedra::BaseDisplayData * manager = Find(pallet);
	if (manager == nullptr)
	{
		manager = Make(pallet);
	}
	return manager;
}

unsigned int NewPolyHedra::BaseDisplayDataManager::InstancesFullCount() const
{
	return Container::Loop::SumUInt32(s, NewPolyHedra::BaseDisplayData::InstancesFullCount);
}
unsigned int NewPolyHedra::BaseDisplayDataManager::InstancesWireCount() const
{
	return Container::Loop::SumUInt32(s, NewPolyHedra::BaseDisplayData::InstancesWireCount);
}

void NewPolyHedra::BaseDisplayDataManager::InstancesClear()
{
	Container::Loop::Invoke(s, NewPolyHedra::BaseDisplayData::InstancesFullClear);
	Container::Loop::Invoke(s, NewPolyHedra::BaseDisplayData::InstancesWireClear);
}
/*void NewPolyHedra::BaseDisplayDataManager::InstancesMake() { }*/

void NewPolyHedra::BaseDisplayDataManager::GraphicsCreate()
{
	ShaderFull.Create();
	ShaderWire.Create();
	Container::Loop::Invoke(s, NewPolyHedra::BaseDisplayData::GraphicsCreate);
}
void NewPolyHedra::BaseDisplayDataManager::GraphicsDelete()
{
	ShaderFull.Delete();
	ShaderWire.Delete();
	Container::Loop::Invoke(s, NewPolyHedra::BaseDisplayData::GraphicsDelete);
}
void NewPolyHedra::BaseDisplayDataManager::GraphicsDrawFull()
{
	ShaderFull.Bind();
	Container::Loop::Invoke(s, NewPolyHedra::BaseDisplayData::GraphicsDrawFull);
	VertexArray::Base::BindNone();
}
void NewPolyHedra::BaseDisplayDataManager::GraphicsDrawWire()
{
	ShaderWire.Bind();
	Container::Loop::Invoke(s, NewPolyHedra::BaseDisplayData::GraphicsDrawWire);
	VertexArray::Base::BindNone();
}
