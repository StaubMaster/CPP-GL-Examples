#include "PropertyControl/Trans3D.hpp"



UI::Control::Trans3D::~Trans3D()
{ }
UI::Control::Trans3D::Trans3D(const char * name)
	: PropertyControl(name)
	, Position("Position")
	, Rotation("Rotation")
	, Object(nullptr)
{
	Position.Anchor.X.AnchorBoth(0, 0);
	Rotation.Anchor.X.AnchorBoth(0, 0);

	ChildInsert(Position);
	ChildInsert(Rotation);

	HideProperty();
}



void UI::Control::Trans3D::Update()
{
	Position.Update();
	Rotation.Update();
}

void UI::Control::Trans3D::Change(::Trans3D * obj)
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
