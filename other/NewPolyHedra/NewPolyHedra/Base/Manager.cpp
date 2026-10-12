#include "NewPolyHedra/Base/Manager.hpp"

#include "NewPolyHedra/Base/Logical/Data.hpp"
#include "NewPolyHedra/Base/Logical/DataManager.hpp"

#include "NewPolyHedra/Base/Display/Data.hpp"
#include "NewPolyHedra/Base/Display/DataManager.hpp"

#include "NewPolyHedra/Pallet/.hpp"
#include "NewPolyHedra/Pallet/Manager.hpp"

#include "Generics/Loop.hpp"



void NewPolyHedra::BaseManager::CleanObjects()
{
	LogicalBase().Clean();
}

unsigned int NewPolyHedra::BaseManager::InstancesFullCount() const
{
	return DisplayBase().InstancesFullCount();
}
unsigned int NewPolyHedra::BaseManager::InstancesWireCount() const
{
	return DisplayBase().InstancesWireCount();
}

void NewPolyHedra::BaseManager::InstancesClear()
{
	DisplayBase().InstancesClear();
}
void NewPolyHedra::BaseManager::InstancesMake()
{
	LogicalBase().InstancesMake();
}

void NewPolyHedra::BaseManager::GraphicsCreate()
{
	DisplayBase().GraphicsCreate();
}
void NewPolyHedra::BaseManager::GraphicsDelete()
{
	DisplayBase().GraphicsDelete();
}
void NewPolyHedra::BaseManager::GraphicsDrawFull()
{
	DisplayBase().GraphicsDrawFull();
}
void NewPolyHedra::BaseManager::GraphicsDrawWire()
{
	DisplayBase().GraphicsDrawWire();
}
