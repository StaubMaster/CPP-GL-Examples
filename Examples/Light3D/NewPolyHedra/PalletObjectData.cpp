#include "PalletObjectData.hpp"
#include "PalletObjectManager.hpp"



void NewPolyHedra_PalletObjectData::ShowFull() { DisplayFull = true; }
void NewPolyHedra_PalletObjectData::HideFull() { DisplayFull = false; }
bool NewPolyHedra_PalletObjectData::VisibleFull() const { return DisplayFull; }

void NewPolyHedra_PalletObjectData::ShowWire() { DisplayWire = true; }
void NewPolyHedra_PalletObjectData::HideWire() { DisplayWire = false; }
bool NewPolyHedra_PalletObjectData::VisibleWire() const { return DisplayWire; }



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
