#include "PalletObjectData.hpp"
#include "PalletObjectManager.hpp"
#include "ObjectData.hpp"



NewPolyHedra_PalletObjectData::~NewPolyHedra_PalletObjectData()
{
	delete ObjectData;
}
NewPolyHedra_PalletObjectData::NewPolyHedra_PalletObjectData()
	: Manager(nullptr)
	, ObjectData(nullptr)
	, Remove(false)
	, Display(true)
{ }



void NewPolyHedra_PalletObjectData::InstancePut() const
{
	if (Manager != nullptr && Display)
	{
		Manager -> InstancePut(ObjectData);
	}
}
