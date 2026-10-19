#include "NewPolyHedra/Base/Display/ObjectManager.hpp"
#include "NewPolyHedra/Base/Display/Object.hpp"

#include "NewPolyHedra/Pallet/Manager.hpp"

#include "Generics/Loop.hpp"
#include "Graphics/VertexArray/Base.hpp"



NewPolyHedra::BaseDisplayObjectManager::~BaseDisplayObjectManager()
{
	Container::Loop::Delete(Objects);
}

unsigned int NewPolyHedra::BaseDisplayObjectManager::Count() const
{
	return Objects.Count();
}

NewPolyHedra::BaseDisplayObject * NewPolyHedra::BaseDisplayObjectManager::Find(const NewPolyHedra::Pallet & pallet) const
{
	return Container::Loop::Find(Objects, &NewPolyHedra::BaseDisplayObject::Equals, &pallet);
}
NewPolyHedra::BaseDisplayObject & NewPolyHedra::BaseDisplayObjectManager::Make(NewPolyHedra::Pallet & pallet)
{
	BaseDisplayObject * manager = NewBase(pallet);

	manager -> GraphicsCreate();
	manager -> GraphicsInitFull(BufferFullMainLayout, BufferFullInstLayout);
	manager -> GraphicsInitWire(BufferWireMainLayout, BufferWireInstLayout);
	VertexArray::Base::BindNone();

	Objects.Insert(manager);
	return *manager;
}
NewPolyHedra::BaseDisplayObject & NewPolyHedra::BaseDisplayObjectManager::Take(NewPolyHedra::Pallet & pallet)
{
	NewPolyHedra::BaseDisplayObject * manager = Find(pallet);
	if (manager != nullptr)
	{
		return *manager;
	}
	return Make(pallet);
}

NewPolyHedra::BaseDisplayObject * NewPolyHedra::BaseDisplayObjectManager::Find(const Pallet * pallet) const
{
	if (pallet == nullptr) { return nullptr; }
	return Find(*pallet);
}
NewPolyHedra::BaseDisplayObject * NewPolyHedra::BaseDisplayObjectManager::Make(Pallet * pallet)
{
	if (pallet == nullptr) { return nullptr; }
	return &Make(*pallet);
}
NewPolyHedra::BaseDisplayObject * NewPolyHedra::BaseDisplayObjectManager::Take(Pallet * pallet)
{
	if (pallet == nullptr) { return nullptr; }
	return &Take(*pallet);
}

unsigned int NewPolyHedra::BaseDisplayObjectManager::InstancesFullCount() const
{
	return Container::Loop::SumUInt32(Objects, &NewPolyHedra::BaseDisplayObject::InstancesFullCount);
}
unsigned int NewPolyHedra::BaseDisplayObjectManager::InstancesWireCount() const
{
	return Container::Loop::SumUInt32(Objects, &NewPolyHedra::BaseDisplayObject::InstancesWireCount);
}

void NewPolyHedra::BaseDisplayObjectManager::InstancesClear()
{
	Container::Loop::Invoke(Objects, &NewPolyHedra::BaseDisplayObject::InstancesFullClear);
	Container::Loop::Invoke(Objects, &NewPolyHedra::BaseDisplayObject::InstancesWireClear);
}
/*void NewPolyHedra::BaseDisplayObjectManager::InstancesMake() { }*/

void NewPolyHedra::BaseDisplayObjectManager::GraphicsCreate()
{
	ShaderFull.Create();
	ShaderWire.Create();
	Container::Loop::Invoke(Objects, &NewPolyHedra::BaseDisplayObject::GraphicsCreate);
}
void NewPolyHedra::BaseDisplayObjectManager::GraphicsDelete()
{
	ShaderFull.Delete();
	ShaderWire.Delete();
	Container::Loop::Invoke(Objects, &NewPolyHedra::BaseDisplayObject::GraphicsDelete);
}
void NewPolyHedra::BaseDisplayObjectManager::GraphicsDrawFull()
{
	ShaderFull.Bind();
	Container::Loop::Invoke(Objects, &NewPolyHedra::BaseDisplayObject::GraphicsDrawFull);
	VertexArray::Base::BindNone();
}
void NewPolyHedra::BaseDisplayObjectManager::GraphicsDrawWire()
{
	ShaderWire.Bind();
	Container::Loop::Invoke(Objects, &NewPolyHedra::BaseDisplayObject::GraphicsDrawWire);
	VertexArray::Base::BindNone();
}
