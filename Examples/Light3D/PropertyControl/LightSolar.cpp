#include "PropertyControl/LightSolar.hpp"



UI::Control::LightSolar::~LightSolar()
{ }
UI::Control::LightSolar::LightSolar(const char * name)
	: PropertyControl(name)
	, Base("Base")
	, Dir("Dir")
	, Object(nullptr)
{
	Base.Anchor.X.AnchorBoth(0, 0);
	Dir.Anchor.X.AnchorBoth(0, 0);

	ChildInsert(Base);
	ChildInsert(Dir);

	AnchorFitChildrenY();
}



void UI::Control::LightSolar::Update()
{
	Base.Update();
	Dir.Update();
}

void UI::Control::LightSolar::Change(::LightSolar * obj)
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
