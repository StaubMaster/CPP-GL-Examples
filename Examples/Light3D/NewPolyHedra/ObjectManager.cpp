#include "ObjectManager.hpp"
#include "PalletObjectManager.hpp"
#include "PalletObjectData.hpp"



NewPolyHedra_PalletObjectManager * NewPolyHedra_ObjectManager::FindPalletObjectManager(NewPolyHedra_Pallet * pallet) const
{
	if (pallet == nullptr) { return nullptr; }
	for (unsigned int i = 0; i < Managers.Count(); i++)
	{
		NewPolyHedra_PalletObjectManager * manager = Managers[i];
		if (manager == nullptr) { continue; }
		if (manager -> Pallet == pallet)
		{
			return manager;
		}
	}
	return nullptr;
}
NewPolyHedra_PalletObjectManager * NewPolyHedra_ObjectManager::MakePalletObjectManager(NewPolyHedra_Pallet * pallet)
{
	if (pallet == nullptr) { return nullptr; }
	NewPolyHedra_PalletObjectManager * manager = NewPalletObjectManager();
	manager -> Pallet = pallet;
	if (BufferLayout != nullptr)
	{
		manager -> Buffer.Init(*BufferLayout);
	}
	manager -> BufferUniform = BufferUniform;
	manager -> GraphicsCreate();
	manager -> VertexBufferInit();
	Managers.Insert(manager);
	return manager;
}
NewPolyHedra_PalletObjectManager * NewPolyHedra_ObjectManager::FindMakePalletObjectManager(NewPolyHedra_Pallet * pallet)
{
	if (pallet == nullptr) { return nullptr; }
	NewPolyHedra_PalletObjectManager * manager = FindPalletObjectManager(pallet);
	if (manager == nullptr)
	{
		manager = MakePalletObjectManager(pallet);
	}
	return manager;
}



NewPolyHedra_PalletObjectData * NewPolyHedra_ObjectManager::NewPalletObjectData(NewPolyHedra_Pallet * pallet)
{
	if (pallet == nullptr) { return nullptr; }
	NewPolyHedra_PalletObjectData * pallet_object_data = new NewPolyHedra_PalletObjectData();
	pallet_object_data -> Manager = FindMakePalletObjectManager(pallet);
	pallet_object_data -> ObjectData = NewObjectData();
	PalletObjectDatas.Insert(pallet_object_data);
	return pallet_object_data;
}

void NewPolyHedra_ObjectManager::UpdatePalletObjectDatas()
{
	for (unsigned int i = 0; i < PalletObjectDatas.Count(); i++)
	{
		NewPolyHedra_PalletObjectData * object = PalletObjectDatas[i];
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



void NewPolyHedra_ObjectManager::InstancesClear()
{
	for (unsigned int i = 0; i < Managers.Count(); i++)
	{
		NewPolyHedra_PalletObjectManager * manager = Managers[i];
		if (manager == nullptr) { continue; }
		manager -> InstancesClear();
	}
}
void NewPolyHedra_ObjectManager::InstancesMake()
{
	for (unsigned int i = 0; i < PalletObjectDatas.Count(); i++)
	{
		NewPolyHedra_PalletObjectData * object = PalletObjectDatas[i];
		if (object == nullptr) { continue; }
		object -> InstancePut();
	}
}



void NewPolyHedra_ObjectManager::GraphicsCreate()
{
	Shader.Create();
	for (unsigned int i = 0; i < Managers.Count(); i++)
	{
		NewPolyHedra_PalletObjectManager * manager = Managers[i];
		if (manager == nullptr) { continue; }
		manager -> GraphicsCreate();
	}
}
void NewPolyHedra_ObjectManager::GraphicsDelete()
{
	Shader.Delete();
	for (unsigned int i = 0; i < Managers.Count(); i++)
	{
		NewPolyHedra_PalletObjectManager * manager = Managers[i];
		if (manager == nullptr) { continue; }
		manager -> GraphicsDelete();
	}
}
void NewPolyHedra_ObjectManager::GraphicsDraw()
{
	Shader.Bind();
	for (unsigned int i = 0; i < Managers.Count(); i++)
	{
		NewPolyHedra_PalletObjectManager * manager = Managers[i];
		if (manager == nullptr) { continue; }
		manager -> GraphicsDraw();
	}
	VertexArray::BindNone();
}
