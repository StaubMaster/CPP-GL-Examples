#include "Manager.hpp"
#include "Pallet.hpp"
#include "ObjectManager.hpp"



NewPolyHedra_Pallet * NewPolyHedra_Manager::FindPallet(PolyHedra * polyhedra) const
{
	if (polyhedra == nullptr) { return nullptr; }
	for (unsigned int i = 0; i < Pallets.Count(); i++)
	{
		NewPolyHedra_Pallet * pallet = Pallets[i];
		if (pallet == nullptr) { continue; }
		if (pallet -> Object == polyhedra)
		{
			return pallet;
		}
	}
	return nullptr;
}
NewPolyHedra_Pallet * NewPolyHedra_Manager::MakePallet(PolyHedra * polyhedra)
{
	if (polyhedra == nullptr) { return nullptr; }
	NewPolyHedra_Pallet * pallet = new NewPolyHedra_Pallet();
	pallet -> Object = polyhedra;
	Pallets.Insert(pallet);
	return pallet;
}
NewPolyHedra_Pallet * NewPolyHedra_Manager::FindMakePallet(PolyHedra * polyhedra)
{
	if (polyhedra == nullptr) { return nullptr; }
	NewPolyHedra_Pallet * pallet = FindPallet(polyhedra);
	if (pallet == nullptr)
	{
		pallet = MakePallet(polyhedra);
	}
	return pallet;
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



void NewPolyHedra_Manager::Draw()
{
	for (unsigned int i = 0; i < ObjectManagers.Count(); i++)
	{
		NewPolyHedra_ObjectManager * manager = ObjectManagers[i];
		if (manager == nullptr) { continue; }
		manager -> Draw();
	}
}



void NewPolyHedra_Manager::GraphicsCreate()
{
	for (unsigned int i = 0; i < Pallets.Count(); i++)
	{
		NewPolyHedra_Pallet * pallet = Pallets[i];
		if (pallet == nullptr) { continue; }
		pallet -> GraphicsCreate();
	}
	for (unsigned int i = 0; i < ObjectManagers.Count(); i++)
	{
		NewPolyHedra_ObjectManager * manager = ObjectManagers[i];
		if (manager == nullptr) { continue; }
		manager -> GraphicsCreate();
	}
}
void NewPolyHedra_Manager::GraphicsDelete()
{
	for (unsigned int i = 0; i < Pallets.Count(); i++)
	{
		NewPolyHedra_Pallet * pallet = Pallets[i];
		if (pallet == nullptr) { continue; }
		pallet -> GraphicsDelete();
	}
	for (unsigned int i = 0; i < ObjectManagers.Count(); i++)
	{
		NewPolyHedra_ObjectManager * manager = ObjectManagers[i];
		if (manager == nullptr) { continue; }
		manager -> GraphicsDelete();
	}
}
