#include "NewPolyHedra/Base/Logical/Object.hpp"
#include "NewPolyHedra/Base/Display/Object.hpp"



void NewPolyHedra::BaseLogicalObject::ShowFull() { DisplayFull = true; }
void NewPolyHedra::BaseLogicalObject::HideFull() { DisplayFull = false; }
bool NewPolyHedra::BaseLogicalObject::VisibleFull() const { return DisplayFull; }

void NewPolyHedra::BaseLogicalObject::ShowWire() { DisplayWire = true; }
void NewPolyHedra::BaseLogicalObject::HideWire() { DisplayWire = false; }
bool NewPolyHedra::BaseLogicalObject::VisibleWire() const { return DisplayWire; }



NewPolyHedra::BaseLogicalObject::BaseLogicalObject(BaseDisplayObject * graphics)
	: Graphics(graphics)
{ }



void NewPolyHedra::BaseLogicalObject::InstancePut() const
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
