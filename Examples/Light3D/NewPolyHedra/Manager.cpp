#include "Manager.hpp"
#include "Pallet.hpp"
#include "ObjectManager.hpp"



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
