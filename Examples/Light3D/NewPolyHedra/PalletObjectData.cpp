#include "PalletObjectData.hpp"
#include "PalletObjectManager.hpp"
#include "ObjectData.hpp"



NewPolyHedra_PalletObjectData::~NewPolyHedra_PalletObjectData()
{
	delete ObjectData;
}
NewPolyHedra_PalletObjectData::NewPolyHedra_PalletObjectData()
	: Remove(false)
	, Display(true)
	, Manager(nullptr)
	, ObjectData(nullptr)
{ }



void NewPolyHedra_PalletObjectData::InstancePut() const
{
	if (Manager != nullptr && Display)
	{
		Manager -> InstancePut(ObjectData);
	}
}
