#include "ObjectManager.hpp"
#include "PalletObjectManager.hpp"
#include "PalletObjectData.hpp"
#include "Pallet.hpp"
#include "PalletManager.hpp"



NewPolyHedra::ObjectManager::~ObjectManager()
{
	for (unsigned int i = 0; i < PalletObjectManagers.Count(); i++)
	{
		delete PalletObjectManagers[i];
	}
}



unsigned int NewPolyHedra::ObjectManager::PalletObjectManagersCount() const
{
	return PalletObjectManagers.Count();
}

NewPolyHedra::PalletObjectManager * NewPolyHedra::ObjectManager::PalletObjectManagersFind(NewPolyHedra::Pallet * pallet) const
{
	if (pallet == nullptr) { return nullptr; }
	for (unsigned int i = 0; i < PalletObjectManagers.Count(); i++)
	{
		NewPolyHedra::PalletObjectManager * manager = PalletObjectManagers[i];
		if (manager == nullptr) { continue; }
		if (manager -> Pallet == pallet)
		{
			return manager;
		}
	}
	return nullptr;
}
NewPolyHedra::PalletObjectManager * NewPolyHedra::ObjectManager::PalletObjectManagersMake(NewPolyHedra::Pallet * pallet)
{
	if (pallet == nullptr) { return nullptr; }
	NewPolyHedra::PalletObjectManager * manager = PalletObjectManagersNew();
	manager -> Pallet = pallet;

	manager -> GraphicsCreate();

	manager -> BufferFull.Bind();
	manager -> BufferFullInstance.Bind();
	if (BufferFullLayout != nullptr)
	{
		BufferFullLayout -> Bind();
	}
	pallet -> GraphicsInitFull();

	manager -> BufferWire.Bind();
	manager -> BufferWireInstance.Bind();
	if (BufferWireLayout != nullptr)
	{
		BufferWireLayout -> Bind();
	}
	pallet -> GraphicsInitWire();

	VertexArray::Base::BindNone();

	PalletObjectManagers.Insert(manager);
	return manager;
}
NewPolyHedra::PalletObjectManager * NewPolyHedra::ObjectManager::PalletObjectManagersFindMake(NewPolyHedra::Pallet * pallet)
{
	if (pallet == nullptr) { return nullptr; }
	NewPolyHedra::PalletObjectManager * manager = PalletObjectManagersFind(pallet);
	if (manager == nullptr)
	{
		manager = PalletObjectManagersMake(pallet);
	}
	return manager;
}

NewPolyHedra::PalletObjectManager * NewPolyHedra::ObjectManager::PalletObjectManagersFind(PolyHedra * polyhedra) const
{
	if (polyhedra == nullptr) { return nullptr; }
	if (NewPolyHedra::PalletManager::Current == nullptr) { return nullptr; }
	NewPolyHedra::Pallet * pallet = NewPolyHedra::PalletManager::Current -> FindPallet(polyhedra);
	return PalletObjectManagersFind(pallet);
}
NewPolyHedra::PalletObjectManager * NewPolyHedra::ObjectManager::PalletObjectManagersMake(PolyHedra * polyhedra)
{
	if (polyhedra == nullptr) { return nullptr; }
	if (NewPolyHedra::PalletManager::Current == nullptr) { return nullptr; }
	NewPolyHedra::Pallet * pallet = NewPolyHedra::PalletManager::Current -> FindMakePallet(polyhedra);
	return PalletObjectManagersMake(pallet);
}
NewPolyHedra::PalletObjectManager * NewPolyHedra::ObjectManager::PalletObjectManagersFindMake(PolyHedra * polyhedra)
{
	if (polyhedra == nullptr) { return nullptr; }
	NewPolyHedra::PalletObjectManager * manager = PalletObjectManagersFind(polyhedra);
	if (manager == nullptr)
	{
		manager = PalletObjectManagersMake(polyhedra);
	}
	return manager;
}



unsigned int NewPolyHedra::ObjectManager::PalletObjectDatasCount() const
{
	return PalletObjectDatas.Count();
}

NewPolyHedra::PalletObjectData * NewPolyHedra::ObjectManager::PalletObjectDatasNew(NewPolyHedra::Pallet * pallet)
{
	if (pallet == nullptr) { return nullptr; }
	NewPolyHedra::PalletObjectData * pallet_object_data = PalletObjectDatasNew();
	pallet_object_data -> Manager = PalletObjectManagersFindMake(pallet);
	PalletObjectDatas.Insert(pallet_object_data);
	return pallet_object_data;
}
NewPolyHedra::PalletObjectData * NewPolyHedra::ObjectManager::PalletObjectDatasNew(PolyHedra * polyhedra)
{
	if (PalletManager::Current == nullptr) { return nullptr; }
	if (polyhedra == nullptr) { return nullptr; }
	Pallet * pallet = PalletManager::Current -> FindMakePallet(polyhedra);
	return PalletObjectDatasNew(pallet);
}

void NewPolyHedra::ObjectManager::PalletObjectDatasRemove()
{
	for (unsigned int i = 0; i < PalletObjectDatas.Count(); i++)
	{
		NewPolyHedra::PalletObjectData * object = PalletObjectDatas[i];
		if (object == nullptr)
		{
			PalletObjectDatas.RemoveAt(i);
			i--;
		}
		else if (object -> Remove)
		{
			delete object;
			PalletObjectDatas.RemoveAt(i);
			i--;
		}
	}
}



unsigned int NewPolyHedra::ObjectManager::InstancesFullCount() const
{
	unsigned int sum = 0;
	for (unsigned int i = 0; i < PalletObjectManagers.Count(); i++)
	{
		NewPolyHedra::PalletObjectManager * manager = PalletObjectManagers[i];
		if (manager == nullptr) { continue; }
		sum += manager -> InstancesFullCount();
	}
	return sum;
}
unsigned int NewPolyHedra::ObjectManager::InstancesWireCount() const
{
	unsigned int sum = 0;
	for (unsigned int i = 0; i < PalletObjectManagers.Count(); i++)
	{
		NewPolyHedra::PalletObjectManager * manager = PalletObjectManagers[i];
		if (manager == nullptr) { continue; }
		sum += manager -> InstancesWireCount();
	}
	return sum;
}

void NewPolyHedra::ObjectManager::InstancesClear()
{
	for (unsigned int i = 0; i < PalletObjectManagers.Count(); i++)
	{
		NewPolyHedra::PalletObjectManager * manager = PalletObjectManagers[i];
		if (manager == nullptr) { continue; }
		manager -> InstancesFullClear();
		manager -> InstancesWireClear();
	}
}
void NewPolyHedra::ObjectManager::InstancesMake()
{
	for (unsigned int i = 0; i < PalletObjectDatas.Count(); i++)
	{
		NewPolyHedra::PalletObjectData * object = PalletObjectDatas[i];
		if (object == nullptr) { continue; }
		object -> InstancePut();
	}
}

void NewPolyHedra::ObjectManager::GraphicsCreate()
{
	ShaderFull.Create();
	ShaderWire.Create();
	for (unsigned int i = 0; i < PalletObjectManagers.Count(); i++)
	{
		NewPolyHedra::PalletObjectManager * manager = PalletObjectManagers[i];
		if (manager == nullptr) { continue; }
		manager -> GraphicsCreate();
	}
}
void NewPolyHedra::ObjectManager::GraphicsDelete()
{
	ShaderFull.Delete();
	ShaderWire.Delete();
	for (unsigned int i = 0; i < PalletObjectManagers.Count(); i++)
	{
		NewPolyHedra::PalletObjectManager * manager = PalletObjectManagers[i];
		if (manager == nullptr) { continue; }
		manager -> GraphicsDelete();
	}
}
void NewPolyHedra::ObjectManager::GraphicsDrawFull()
{
	ShaderFull.Bind();
	for (unsigned int i = 0; i < PalletObjectManagers.Count(); i++)
	{
		NewPolyHedra::PalletObjectManager * manager = PalletObjectManagers[i];
		if (manager == nullptr) { continue; }
		manager -> GraphicsDrawFull();
	}
	VertexArray::Base::BindNone();
}
void NewPolyHedra::ObjectManager::GraphicsDrawWire()
{
	ShaderWire.Bind();
	for (unsigned int i = 0; i < PalletObjectManagers.Count(); i++)
	{
		NewPolyHedra::PalletObjectManager * manager = PalletObjectManagers[i];
		if (manager == nullptr) { continue; }
		manager -> GraphicsDrawWire();
	}
	VertexArray::Base::BindNone();
}
