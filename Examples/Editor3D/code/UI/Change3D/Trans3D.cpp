#include "UI/Change3D/Trans3D.hpp"

#include "Ray3D_Hit.hpp"
#include "ValueType/Ray/Hit/F3Type.hpp"



#include "Generics/Loop.hpp"

// put in Container::Loop
// these have double args to allow conversion if not identical



Change3D::Trans3D::Trans3D()
	: Collection()
{
	Changes.Insert(&Position);
	Changes.Insert(&Rotation);
}



::Trans3D Change3D::Trans3D::Get() const
{
	return ::Trans3D(
		Position.Get(),
		Rotation.Get()
	);
}
void Change3D::Trans3D::Set(const ::Trans3D & val)
{
	Position.Set(val.Position);
	Rotation.Set(val.Rotation);
	Rotation.CenterChange(val.Position);
}

void Change3D::Trans3D::ChangeValue(const RayF3 & ray)
{
	Collection::ChangeValue(ray);
	Rotation.CenterChange(Position.Get());
}
