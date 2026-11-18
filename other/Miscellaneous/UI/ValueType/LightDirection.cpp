#include "UI/ValueType/LightDirection.hpp"



UI::LightDirection::LightDirection(const char * name)
	: NestedProperty(name)
	, Base("Base")
	, Dir("Dir")
	, Object(nullptr)
{
	Base.Make_Anchor_X_Both(nullptr, nullptr);
	Dir.Make_Anchor_X_Both(nullptr, nullptr);

	ChildInsert(Base);
	ChildInsert(Dir);

	Minimize();
}



void UI::LightDirection::Syncronize()
{
	Base.Syncronize();
	Dir.Syncronize();
}

void UI::LightDirection::Change(::LightDirection * obj)
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
