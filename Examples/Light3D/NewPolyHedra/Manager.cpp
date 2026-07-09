#include "Manager.hpp"
#include "PalletManager.hpp"
#include "ObjectManager.hpp"



void NewPolyHedra::Manager::UpdatePalletObjectDatas()
{
	for (unsigned int i = 0; i < ObjectManagers.Count(); i++)
	{
		NewPolyHedra::ObjectManager * manager = ObjectManagers[i];
		if (manager == nullptr) { continue; }
		manager -> UpdatePalletObjectDatas();
	}
}



void NewPolyHedra::Manager::InstancesClear()
{
	for (unsigned int i = 0; i < ObjectManagers.Count(); i++)
	{
		NewPolyHedra::ObjectManager * manager = ObjectManagers[i];
		if (manager == nullptr) { continue; }
		manager -> InstancesClear();
	}
}
void NewPolyHedra::Manager::InstancesMake()
{
	for (unsigned int i = 0; i < ObjectManagers.Count(); i++)
	{
		NewPolyHedra::ObjectManager * manager = ObjectManagers[i];
		if (manager == nullptr) { continue; }
		manager -> InstancesMake();
	}
}



void NewPolyHedra::Manager::GraphicsCreate()
{
	if (PalletManager != nullptr)
	{
		PalletManager -> GraphicsCreate();
	}
	for (unsigned int i = 0; i < ObjectManagers.Count(); i++)
	{
		NewPolyHedra::ObjectManager * manager = ObjectManagers[i];
		if (manager == nullptr) { continue; }
		manager -> GraphicsCreate();
	}
}
void NewPolyHedra::Manager::GraphicsDelete()
{
	if (PalletManager != nullptr)
	{
		PalletManager -> GraphicsDelete();
	}
	for (unsigned int i = 0; i < ObjectManagers.Count(); i++)
	{
		NewPolyHedra::ObjectManager * manager = ObjectManagers[i];
		if (manager == nullptr) { continue; }
		manager -> GraphicsDelete();
	}
}
void NewPolyHedra::Manager::GraphicsDrawFull()
{
	for (unsigned int i = 0; i < ObjectManagers.Count(); i++)
	{
		NewPolyHedra::ObjectManager * manager = ObjectManagers[i];
		if (manager == nullptr) { continue; }
		manager -> GraphicsDrawFull();
	}
}
void NewPolyHedra::Manager::GraphicsDrawWire()
{
	for (unsigned int i = 0; i < ObjectManagers.Count(); i++)
	{
		NewPolyHedra::ObjectManager * manager = ObjectManagers[i];
		if (manager == nullptr) { continue; }
		manager -> GraphicsDrawWire();
	}
}
