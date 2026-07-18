#include "ValueTypeUI/LightDirection.hpp"



UI::Control::LightDirection::~LightDirection()
{ }
UI::Control::LightDirection::LightDirection(const char * name)
	: PropertyControl(name)
	, Base("Base")
	, Dir("Dir")
	, Object(nullptr)
{
	Base.Anchor.X.AnchorBoth(0, 0);
	Dir.Anchor.X.AnchorBoth(0, 0);

	ChildInsert(Base);
	ChildInsert(Dir);

	HideProperty();
}



void UI::Control::LightDirection::Update()
{
	Base.Update();
	Dir.Update();
}

void UI::Control::LightDirection::Change(::LightDirection * obj)
{
	Object = obj;
	if (Object != nullptr)
	{
		Base.Change(&(Object -> Base));
		Dir.Change(&(Object -> Dir));
	}
	else
	{
		Base.Change(nullptr);
		Dir.Change(nullptr);
	}
}
