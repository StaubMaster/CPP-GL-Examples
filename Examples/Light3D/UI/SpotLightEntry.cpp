#include "UI/SpotLightEntry.hpp"



UI::SpotLightEntry::~SpotLightEntry()
{ }
UI::SpotLightEntry::SpotLightEntry()
	: UI::Control::Form()
	, Origin("Origin")
	, Target("Target")
	, Light("Light")
{
	Anchor.X.AnchorMin(0, 400);
	Anchor.Y.AnchorMin(0, 0);

	Origin.Anchor.X.AnchorBoth(0, 0);
	Target.Anchor.X.AnchorBoth(0, 0);
	Light.Anchor.X.AnchorBoth(0, 0);

	ChildInsert(Origin);
	ChildInsert(Target);
	ChildInsert(Light);

	AnchorFitChildrenY();

	Change(nullptr);
}



#include "../SpotLightEntry.hpp"

void UI::SpotLightEntry::Change(::SpotLightEntry * obj)
{
	Object = obj;
	if (Object != nullptr)
	{
		Origin.Change(&(Object -> Origin));
		Target.Change(&(Object -> Target));
		Light.Change(Object -> Light);
	}
	else
	{
		Origin.Change(nullptr);
		Target.Change(nullptr);
		Light.Change(nullptr);
	}
}


