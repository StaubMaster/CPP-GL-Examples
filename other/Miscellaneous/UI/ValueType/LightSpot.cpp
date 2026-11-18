#include "UI/ValueType/LightSpot.hpp"



UI::LightSpot::LightSpot(const char * name)
	: NestedProperty(name)
	, Base("Base")
	, Pos("Pos")
	, Dir("Dir")
	, Object(nullptr)
{
	Base.Make_Anchor_X_Both(nullptr, nullptr);
	Pos.Make_Anchor_X_Both(nullptr, nullptr);
	Dir.Make_Anchor_X_Both(nullptr, nullptr);

	ChildInsert(Base);
	ChildInsert(Pos);
	ChildInsert(Dir);

	Minimize();
}



void UI::LightSpot::Syncronize()
{
	Base.Syncronize();
	Pos.Syncronize();
	Dir.Syncronize();
}

void UI::LightSpot::Change(::LightSpot * obj)
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
