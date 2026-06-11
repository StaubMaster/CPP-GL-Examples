#include "PropertyControl/LightSpot.hpp"



UI::Control::LightSpot::~LightSpot()
{ }
UI::Control::LightSpot::LightSpot(const char * name)
	: PropertyControl(name)
	, Base("Base")
	, Pos("Pos")
	, Dir("Dir")
	, Object(nullptr)
{
	Base.Anchor.X.AnchorBoth(0, 0);
	Pos.Anchor.X.AnchorBoth(0, 0);
	Dir.Anchor.X.AnchorBoth(0, 0);

	ChildInsert(Base);
	ChildInsert(Pos);
	ChildInsert(Dir);

	AnchorFitChildrenY();
}



void UI::Control::LightSpot::Update()
{
	Base.Update();
	Pos.Update();
	Dir.Update();
}

void UI::Control::LightSpot::Change(::LightSpot * obj)
{
	Object = obj;
	if (Object != nullptr)
	{
		Base.Change(&(Object -> Base));
		Pos.Change(&(Object -> Pos));
		Dir.Change(&(Object -> Dir));
	}
	else
	{
		Base.Change(nullptr);
		Pos.Change(nullptr);
		Dir.Change(nullptr);
	}
}
