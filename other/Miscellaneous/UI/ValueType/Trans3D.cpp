#include "UI/ValueType/Trans3D.hpp"



UI::Trans3D::Trans3D(const char * name)
	: NestedProperty(name)
	, Position("Position")
	, Rotation("Rotation")
	, Object(nullptr)
{
	Position.Make_Anchor_X_Both(nullptr, nullptr);
	Rotation.Make_Anchor_X_Both(nullptr, nullptr);

	ChildInsert(Position);
	ChildInsert(Rotation);

	Minimize();
}



void UI::Trans3D::Syncronize()
{
	Position.Syncronize();
	Rotation.Syncronize();
}

void UI::Trans3D::Change(::Trans3D * obj)
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
