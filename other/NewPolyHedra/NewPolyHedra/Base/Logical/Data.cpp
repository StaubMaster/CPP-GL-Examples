#include "NewPolyHedra/Base/Logical/Data.hpp"
#include "NewPolyHedra/Base/Display/Data.hpp"



void NewPolyHedra::BaseLogicalData::ShowFull() { DisplayFull = true; }
void NewPolyHedra::BaseLogicalData::HideFull() { DisplayFull = false; }
bool NewPolyHedra::BaseLogicalData::VisibleFull() const { return DisplayFull; }

void NewPolyHedra::BaseLogicalData::ShowWire() { DisplayWire = true; }
void NewPolyHedra::BaseLogicalData::HideWire() { DisplayWire = false; }
bool NewPolyHedra::BaseLogicalData::VisibleWire() const { return DisplayWire; }



NewPolyHedra::BaseLogicalData::BaseLogicalData(BaseDisplayData * graphics)
	: Graphics(graphics)
{ }



void NewPolyHedra::BaseLogicalData::InstancePut() const
{
	if (Graphics != nullptr)
	{
		if (DisplayFull)
		{
			Graphics -> InstancesFullPut(DataVoid());
		}
		if (DisplayWire)
		{
			Graphics -> InstancesWirePut(DataVoid());
		}
	}
}
