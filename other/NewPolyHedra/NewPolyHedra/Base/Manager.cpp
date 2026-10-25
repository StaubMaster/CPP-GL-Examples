#include "NewPolyHedra/Base/Manager.hpp"

#include "NewPolyHedra/Base/Logical/Object.hpp"
#include "NewPolyHedra/Base/Logical/ObjectManager.hpp"

#include "NewPolyHedra/Base/Display/Object.hpp"
#include "NewPolyHedra/Base/Display/ObjectManager.hpp"

#include "NewPolyHedra/Pallet/.hpp"
#include "NewPolyHedra/Pallet/Manager.hpp"

#include "Generics/Loop.hpp"



void NewPolyHedra::BaseManager::CleanObjects()
{
	LogicalManager().Clean();
}

unsigned int NewPolyHedra::BaseManager::InstancesFullCount() const
{
	return DisplayManager().InstancesFullCount();
}
unsigned int NewPolyHedra::BaseManager::InstancesWireCount() const
{
	return DisplayManager().InstancesWireCount();
}

void NewPolyHedra::BaseManager::InstancesClear()
{
	DisplayManager().InstancesClear();
}
void NewPolyHedra::BaseManager::InstancesMake()
{
	LogicalManager().InstancesMake();
}

void NewPolyHedra::BaseManager::GraphicsCreate()
{
	DisplayManager().GraphicsCreate();
}
void NewPolyHedra::BaseManager::GraphicsDelete()
{
	DisplayManager().GraphicsDelete();
}
void NewPolyHedra::BaseManager::GraphicsDrawFull()
{
	DisplayManager().GraphicsDrawFull();
}
void NewPolyHedra::BaseManager::GraphicsDrawWire()
{
	DisplayManager().GraphicsDrawWire();
}
