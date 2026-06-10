#include "UI/LightObject.hpp"



UI::SpotLightEntry::~SpotLightEntry()
{ }
UI::SpotLightEntry::SpotLightEntry()
	: UI::Control::Form()
	, Position()
	, Target()
	, Light()
{
	Position.Anchor.X.AnchorBoth(0, 0);
	Position.Anchor.Y.AnchorMin(0);

	Target.Anchor.X.AnchorBoth(0, 0);
	Target.Anchor.Y.AnchorMin(Position.Anchor.Y.GetMinSize());

	Light.Anchor.X.AnchorBoth(0, 0);
	Light.Anchor.Y.AnchorMin(Target.Anchor.Y.GetMinSize());

	Anchor.X.AnchorMin(0, 400);
	Anchor.Y.AnchorMin(0, Light.Anchor.Y.GetMinSize() + Light.AnchorMargin.Max.Y + AnchorBoarder.Max.Y + AnchorPadding.Max.Y);

	ChildInsert(Position);
	ChildInsert(Target);
	ChildInsert(Light);

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


