#include "PalletObjectData.hpp"
#include "PalletObjectManager.hpp"



NewPolyHedra_PalletObjectData::~NewPolyHedra_PalletObjectData()
{ }
NewPolyHedra_PalletObjectData::NewPolyHedra_PalletObjectData()
	: Remove(false)
	, DisplayFull(true)
	, DisplayWire(false)
	, Manager(nullptr)
{ }



void NewPolyHedra_PalletObjectData::InstancePut() const
{
	if (Manager != nullptr)
	{
		if (DisplayFull)
		{
			Manager -> InstancePutFull(DataVoid());
		}
		if (DisplayWire)
		{
			Manager -> InstancePutWire(DataVoid());
		}
	}
}
