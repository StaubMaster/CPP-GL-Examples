#include "UI/LightObject.hpp"



UI::SpotLightEntry::~SpotLightEntry()
{ }
UI::SpotLightEntry::SpotLightEntry()
	: UI::Control::Form()
	, Position("Position")
	, Target("Target")
	, Light()
{
	Anchor.X.AnchorMin(0, 400);
	Anchor.Y.AnchorMin(0, 0);

	Position.Anchor.X.AnchorBoth(0, 0);
	Target.Anchor.X.AnchorBoth(0, 0);
	Light.Anchor.X.AnchorBoth(0, 0);

	ChildInsert(Position);
	ChildInsert(Target);
	ChildInsert(Light);

	AnchorFitChildrenY();

	Change(nullptr);
}



#include "Context.hpp"

void UI::SpotLightEntry::Change(::SpotLightEntry * obj)
{
	Object = obj;
	if (Object != nullptr)
	{
		Position.Change(&(Object -> Position));
		Target.Change(&(Object -> Target));
		Light.Change(Object -> Light);
	}
	else
	{
		Position.Change(nullptr);
		Target.Change(nullptr);
		Light.Change(nullptr);
	}
}


