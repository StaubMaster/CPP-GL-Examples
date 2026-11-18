#include "ValueTypeUI/Trans3D.hpp"



UI::Control_::Trans3D::Trans3D(const char * name)
	: PropertyControl(name)
	, Position("Position")
	, Rotation("Rotation")
	, Object(nullptr)
{
	//Position.Anchor.X.AnchorBoth(0, 0);
	//Rotation.Anchor.X.AnchorBoth(0, 0);
	Position.Make_Anchor_X_Both(nullptr, nullptr);
	Rotation.Make_Anchor_X_Both(nullptr, nullptr);

	ChildInsert(Position);
	ChildInsert(Rotation);

	Minimize();
}



void UI::Control_::Trans3D::Syncronize()
{
	Position.Syncronize();
	Rotation.Syncronize();
}

void UI::Control_::Trans3D::Change(::Trans3D * obj)
{
	Object = obj;
	if (Object != nullptr)
	{
		Position.Change(&(Object -> Position));
		Rotation.Change(&(Object -> Rotation));
	}
	else
	{
		Position.Change(nullptr);
		Rotation.Change(nullptr);
	}
}
