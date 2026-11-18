#include "ValueTypeUI/LightDirection.hpp"



UI::Control_::LightDirection::LightDirection(const char * name)
	: PropertyControl(name)
	, Base("Base")
	, Dir("Dir")
	, Object(nullptr)
{
	//Base.Anchor.X.AnchorBoth(0, 0);
	//Dir.Anchor.X.AnchorBoth(0, 0);
	Base.Make_Anchor_X_Both(nullptr, nullptr);
	Dir.Make_Anchor_X_Both(nullptr, nullptr);

	ChildInsert(Base);
	ChildInsert(Dir);

	Minimize();
}



void UI::Control_::LightDirection::Syncronize()
{
	Base.Syncronize();
	Dir.Syncronize();
}

void UI::Control_::LightDirection::Change(::LightDirection * obj)
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
