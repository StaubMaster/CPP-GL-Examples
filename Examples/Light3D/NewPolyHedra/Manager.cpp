#include "Manager.hpp"
#include "Pallet.hpp"
#include "ObjectManager.hpp"

#include "Graphics/Buffer/VertexArray.hpp"



void NewPolyHedra_Manager::UpdatePalletObjectDatas()
{
	for (unsigned int i = 0; i < ObjectManagers.Count(); i++)
	{
		NewPolyHedra_ObjectManager * manager = ObjectManagers[i];
		if (manager == nullptr) { continue; }
		manager -> UpdatePalletObjectDatas();
	}
}



void NewPolyHedra_Manager::InstancesClear()
{
	for (unsigned int i = 0; i < ObjectManagers.Count(); i++)
	{
		NewPolyHedra_ObjectManager * manager = ObjectManagers[i];
		if (manager == nullptr) { continue; }
		manager -> InstancesClear();
	}
}
void NewPolyHedra_Manager::InstancesMake()
{
	for (unsigned int i = 0; i < ObjectManagers.Count(); i++)
	{
		NewPolyHedra_ObjectManager * manager = ObjectManagers[i];
		if (manager == nullptr) { continue; }
		manager -> InstancesMake();
	}
}



void NewPolyHedra_Manager::GraphicsCreate()
{
	PalletManager.GraphicsCreate();
	for (unsigned int i = 0; i < ObjectManagers.Count(); i++)
	{
		NewPolyHedra_ObjectManager * manager = ObjectManagers[i];
		if (manager == nullptr) { continue; }
		manager -> GraphicsCreate();
	}
}
void NewPolyHedra_Manager::GraphicsDelete()
{
	PalletManager.GraphicsDelete();
	for (unsigned int i = 0; i < ObjectManagers.Count(); i++)
	{
		NewPolyHedra_ObjectManager * manager = ObjectManagers[i];
		if (manager == nullptr) { continue; }
		manager -> GraphicsDelete();
	}
}
void NewPolyHedra_Manager::GraphicsDrawFull()
{
	for (unsigned int i = 0; i < ObjectManagers.Count(); i++)
	{
		NewPolyHedra_ObjectManager * manager = ObjectManagers[i];
		if (manager == nullptr) { continue; }
		manager -> GraphicsDrawFull();
	}
}
void NewPolyHedra_Manager::GraphicsDrawWire()
{
	for (unsigned int i = 0; i < ObjectManagers.Count(); i++)
	{
		NewPolyHedra_ObjectManager * manager = ObjectManagers[i];
		if (manager == nullptr) { continue; }
		manager -> GraphicsDrawWire();
	}
}
