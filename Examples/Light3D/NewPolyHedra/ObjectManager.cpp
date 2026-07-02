#include "ObjectManager.hpp"
#include "PalletObjectManager.hpp"
#include "PalletObjectData.hpp"



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
