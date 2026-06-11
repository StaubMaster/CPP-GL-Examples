#include "SpotLightEntry.hpp"



SpotLightEntry::~SpotLightEntry()
{ }
SpotLightEntry::SpotLightEntry() :
	Origin(),
	Target(),
	Light(nullptr),
	EntryLight(),
	EntryHolder()
{ }



void SpotLightEntry::Look(VectorF3 origin, VectorF3 target)
{
	Origin = origin;
	Target = target;
}
void SpotLightEntry::Update()
{
	EulerAngle3D angle =EulerAngle3D::PointToZ(Target - Origin);

	if (Light != nullptr)
	{
		Light -> Pos = Origin + angle.forward(VectorF3(0, 0, 3));
		Light -> Dir = (Target - Origin).normalize();
	}

	EntryLight.Trans().Position = Origin;
	EntryLight.Trans().Rotation = angle;

	EntryHolder.Trans().Position = Origin;
	EntryHolder.Trans().Rotation = EulerAngle3D(Angle(), Angle(), angle.Y2);
}



void SpotLightEntry::Toggle()
{
	if (Light -> Base.Intensity == 0.0f)
	{
		Light -> Base.Intensity = 1.0f;
	}
	else
	{
		Light -> Base.Intensity = 0.0f;
	}
}
