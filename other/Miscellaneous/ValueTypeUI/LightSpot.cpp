#include "ValueTypeUI/LightSpot.hpp"



UI::Control_::LightSpot::LightSpot(const char * name)
	: PropertyControl(name)
	, Base("Base")
	, Pos("Pos")
	, Dir("Dir")
	, Object(nullptr)
{
	//Base.Anchor.X.AnchorBoth(0, 0);
	//Pos.Anchor.X.AnchorBoth(0, 0);
	//Dir.Anchor.X.AnchorBoth(0, 0);
	Base.Make_Anchor_X_Both(nullptr, nullptr);
	Pos.Make_Anchor_X_Both(nullptr, nullptr);
	Dir.Make_Anchor_X_Both(nullptr, nullptr);

	ChildInsert(Base);
	ChildInsert(Pos);
	ChildInsert(Dir);

	Minimize();
}



void UI::Control_::LightSpot::Syncronize()
{
	Base.Syncronize();
	Pos.Syncronize();
	Dir.Syncronize();
}

void UI::Control_::LightSpot::Change(::LightSpot * obj)
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
