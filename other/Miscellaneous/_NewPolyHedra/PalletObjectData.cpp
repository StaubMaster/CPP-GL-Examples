#include "PalletObjectData.hpp"
#include "PalletObjectManager.hpp"



void NewPolyHedra::PalletObjectData::ShowFull() { DisplayFull = true; }
void NewPolyHedra::PalletObjectData::HideFull() { DisplayFull = false; }
bool NewPolyHedra::PalletObjectData::VisibleFull() const { return DisplayFull; }

void NewPolyHedra::PalletObjectData::ShowWire() { DisplayWire = true; }
void NewPolyHedra::PalletObjectData::HideWire() { DisplayWire = false; }
bool NewPolyHedra::PalletObjectData::VisibleWire() const { return DisplayWire; }



NewPolyHedra::PalletObjectData::PalletObjectData(PalletObjectManager * manager)
	: Manager(manager)
{ }



void NewPolyHedra::PalletObjectData::InstancePut() const
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
