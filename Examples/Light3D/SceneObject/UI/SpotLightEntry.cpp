#include "SceneObject/UI/SpotLightEntry.hpp"



UI::Control::SpotLightEntry::~SpotLightEntry()
{ }
UI::Control::SpotLightEntry::SpotLightEntry()
	: GroupBox()
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

void UI::Control::SpotLightEntry::Update()
{
	Target.Update();
	Light.Update();
}

void UI::Control::SpotLightEntry::Change(::SpotLightEntry * obj)
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
