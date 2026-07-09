#include "ObjectManager.hpp"
#include "PalletObjectManager.hpp"
#include "PalletObjectData.hpp"
#include "Pallet.hpp"
#include "PalletManager.hpp"



NewPolyHedra::PalletObjectManager * NewPolyHedra::ObjectManager::FindPalletObjectManager(NewPolyHedra::Pallet * pallet) const
{
	if (pallet == nullptr) { return nullptr; }
	for (unsigned int i = 0; i < Managers.Count(); i++)
	{
		NewPolyHedra::PalletObjectManager * manager = Managers[i];
		if (manager == nullptr) { continue; }
		if (manager -> Pallet == pallet)
		{
			return manager;
		}
	}
	return nullptr;
}
NewPolyHedra::PalletObjectManager * NewPolyHedra::ObjectManager::MakePalletObjectManager(NewPolyHedra::Pallet * pallet)
{
	if (pallet == nullptr) { return nullptr; }
	NewPolyHedra::PalletObjectManager * manager = NewPalletObjectManager();
	manager -> Pallet = pallet;
	if (BufferFullLayout != nullptr)
	{
		manager -> BufferFull.Init(*BufferFullLayout);
	}
	if (BufferWireLayout != nullptr)
	{
		manager -> BufferWire.Init(*BufferWireLayout);
	}
	manager -> BufferUniform = BufferUniform;
	manager -> GraphicsCreate();
	manager -> VertexBufferInit();
	Managers.Insert(manager);
	return manager;
}
NewPolyHedra::PalletObjectManager * NewPolyHedra::ObjectManager::FindMakePalletObjectManager(NewPolyHedra::Pallet * pallet)
{
	if (pallet == nullptr) { return nullptr; }
	NewPolyHedra::PalletObjectManager * manager = FindPalletObjectManager(pallet);
	if (manager == nullptr)
	{
		manager = MakePalletObjectManager(pallet);
	}
	return manager;
}



NewPolyHedra::PalletObjectManager * NewPolyHedra::ObjectManager::FindPalletObjectManager(PolyHedra * polyhedra) const
{
	if (polyhedra == nullptr) { return nullptr; }
	if (NewPolyHedra::PalletManager::Current == nullptr) { return nullptr; }
	NewPolyHedra::Pallet * pallet = NewPolyHedra::PalletManager::Current -> FindPallet(polyhedra);
	return FindPalletObjectManager(pallet);
}
NewPolyHedra::PalletObjectManager * NewPolyHedra::ObjectManager::MakePalletObjectManager(PolyHedra * polyhedra)
{
	if (polyhedra == nullptr) { return nullptr; }
	if (NewPolyHedra::PalletManager::Current == nullptr) { return nullptr; }
	NewPolyHedra::Pallet * pallet = NewPolyHedra::PalletManager::Current -> FindMakePallet(polyhedra);
	return MakePalletObjectManager(pallet);
}
NewPolyHedra::PalletObjectManager * NewPolyHedra::ObjectManager::FindMakePalletObjectManager(PolyHedra * polyhedra)
{
	if (polyhedra == nullptr) { return nullptr; }
	NewPolyHedra::PalletObjectManager * manager = FindPalletObjectManager(polyhedra);
	if (manager == nullptr)
	{
		manager = MakePalletObjectManager(polyhedra);
	}
	return manager;
}



NewPolyHedra::PalletObjectData * NewPolyHedra::ObjectManager::NewPalletObjectData(NewPolyHedra::Pallet * pallet)
{
	if (pallet == nullptr) { return nullptr; }
	NewPolyHedra::PalletObjectData * pallet_object_data = NewPalletObjectData();
	pallet_object_data -> Manager = FindMakePalletObjectManager(pallet);
	PalletObjectDatas.Insert(pallet_object_data);
	return pallet_object_data;
}

void NewPolyHedra::ObjectManager::UpdatePalletObjectDatas()
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



void NewPolyHedra::ObjectManager::InstancesClear()
{
	for (unsigned int i = 0; i < Managers.Count(); i++)
	{
		NewPolyHedra::PalletObjectManager * manager = Managers[i];
		if (manager == nullptr) { continue; }
		manager -> InstancesClear();
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
	for (unsigned int i = 0; i < Managers.Count(); i++)
	{
		NewPolyHedra::PalletObjectManager * manager = Managers[i];
		if (manager == nullptr) { continue; }
		manager -> GraphicsCreate();
	}
}
void NewPolyHedra::ObjectManager::GraphicsDelete()
{
	ShaderFull.Delete();
	ShaderWire.Delete();
	for (unsigned int i = 0; i < Managers.Count(); i++)
	{
		NewPolyHedra::PalletObjectManager * manager = Managers[i];
		if (manager == nullptr) { continue; }
		manager -> GraphicsDelete();
	}
}
void NewPolyHedra::ObjectManager::GraphicsDrawFull()
{
	ShaderFull.Bind();
	for (unsigned int i = 0; i < Managers.Count(); i++)
	{
		NewPolyHedra::PalletObjectManager * manager = Managers[i];
		if (manager == nullptr) { continue; }
		manager -> GraphicsDrawFull();
	}
	VertexArray::BindNone();
}
void NewPolyHedra::ObjectManager::GraphicsDrawWire()
{
	ShaderWire.Bind();
	for (unsigned int i = 0; i < Managers.Count(); i++)
	{
		NewPolyHedra::PalletObjectManager * manager = Managers[i];
		if (manager == nullptr) { continue; }
		manager -> GraphicsDrawWire();
	}
	VertexArray::BindNone();
}
