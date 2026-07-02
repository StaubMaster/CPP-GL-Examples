#include "ObjectManager.hpp"
#include "PalletObjectManager.hpp"
#include "PalletObjectData.hpp"



/*NewPolyHedra_PalletObjectManager * NewPolyHedra_ObjectManager::FindPalletManager(NewPolyHedra_Pallet * pallet) const
{
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
}*/
/*NewPolyHedra_PalletObjectManager * NewPolyHedra_ObjectManager::MakePalletManager(NewPolyHedra_Pallet * pallet)
{ }*/
/*NewPolyHedra_PalletObjectManager * NewPolyHedra_ObjectManager::FindMakePalletManager(NewPolyHedra_Pallet * pallet)
{ }*/



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
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		NewPolyHedra_PalletObjectData * object = Objects[i];
		if (object == nullptr) { continue; }
		object -> InstancePut();
	}
}



void NewPolyHedra_ObjectManager::Draw()
{
	Shader.Bind();
	for (unsigned int i = 0; i < Managers.Count(); i++)
	{
		NewPolyHedra_PalletObjectManager * manager = Managers[i];
		if (manager == nullptr) { continue; }
		manager -> Draw();
	}
	VertexArray::BindNone();
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
