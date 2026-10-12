#include "Manager.hpp"
#include "Pallet/Manager.hpp"
#include "Base/Manager.hpp"

#include "Generics/Loop.hpp"



void NewPolyHedra::Manager::CleanObjects()
{
	Container::Loop::Invoke(BaseManagers, NewPolyHedra::BaseManager::CleanObjects);
}



void NewPolyHedra::Manager::InstancesClear()
{
	Container::Loop::Invoke(BaseManagers, NewPolyHedra::BaseManager::InstancesClear);
}
void NewPolyHedra::Manager::InstancesMake()
{
	Container::Loop::Invoke(BaseManagers, NewPolyHedra::BaseManager::InstancesMake);
}



void NewPolyHedra::Manager::GraphicsCreate()
{
	if (PalletManager != nullptr)
	{
		PalletManager -> GraphicsCreate();
	}
	Container::Loop::Invoke(BaseManagers, NewPolyHedra::BaseManager::GraphicsCreate);
}
void NewPolyHedra::Manager::GraphicsDelete()
{
	if (PalletManager != nullptr)
	{
		PalletManager -> GraphicsDelete();
	}
	Container::Loop::Invoke(BaseManagers, NewPolyHedra::BaseManager::GraphicsDelete);
}
void NewPolyHedra::Manager::GraphicsDrawFull()
{
	Container::Loop::Invoke(BaseManagers, NewPolyHedra::BaseManager::GraphicsDrawFull);
}
void NewPolyHedra::Manager::GraphicsDrawWire()
{
	Container::Loop::Invoke(BaseManagers, NewPolyHedra::BaseManager::GraphicsDrawWire);
}
