#include "UserTrans3DChange.hpp"
#include "Ray3D_Hit.hpp"

void UserTrans3DChange::FindIndicator(const Ray3D & ray)
{
	Ray3D_Hit_Type<EIndicatorType> hit(EIndicatorType::None);

	hit.Consider(RayIntersectHit(ray, MoveAxisXIndicator), EIndicatorType::MoveAxisX);
	hit.Consider(RayIntersectHit(ray, MoveAxisYIndicator), EIndicatorType::MoveAxisY);
	hit.Consider(RayIntersectHit(ray, MoveAxisZIndicator), EIndicatorType::MoveAxisZ);

	hit.Consider(RayIntersectHit(ray, SpinRingXIndicator), EIndicatorType::SpinRingX);
	hit.Consider(RayIntersectHit(ray, SpinRingYIndicator), EIndicatorType::SpinRingY);
	hit.Consider(RayIntersectHit(ray, SpinRingZIndicator), EIndicatorType::SpinRingZ);

	if (hit.Is())
	{
		IndicatorOffset = hit.Pos();
		IndicatorHovering = hit.Index;
	}
	else
	{
		IndicatorOffset = VectorF3();
		IndicatorHovering = EIndicatorType::None;
	}
}
void UserTrans3DChange::UpdateIndicator(const View3D & view)
{
	float dist = (view.Trans.Position - Trans.Position).length();

	if (IndicatorHovering == EIndicatorType::None)
	{
		MoveAxisXIndicator.Color() = ColorF4(1, 0, 0);
		MoveAxisYIndicator.Color() = ColorF4(0, 1, 0);
		MoveAxisZIndicator.Color() = ColorF4(0, 0, 1);
		SpinRingXIndicator.Color() = ColorF4(1, 0, 0);
		SpinRingYIndicator.Color() = ColorF4(0, 1, 0);
		SpinRingZIndicator.Color() = ColorF4(0, 0, 1);
	}
	else
	{
		MoveAxisXIndicator.Color() = ColorF4(0.5f, 0.5f, 0.5f);
		MoveAxisYIndicator.Color() = ColorF4(0.5f, 0.5f, 0.5f);
		MoveAxisZIndicator.Color() = ColorF4(0.5f, 0.5f, 0.5f);
		SpinRingXIndicator.Color() = ColorF4(0.5f, 0.5f, 0.5f);
		SpinRingYIndicator.Color() = ColorF4(0.5f, 0.5f, 0.5f);
		SpinRingZIndicator.Color() = ColorF4(0.5f, 0.5f, 0.5f);
		switch (IndicatorHovering)
		{
			case EIndicatorType::MoveAxisX: MoveAxisXIndicator.Color() = ColorF4(1, 0, 0); break;
			case EIndicatorType::MoveAxisY: MoveAxisYIndicator.Color() = ColorF4(0, 1, 0); break;
			case EIndicatorType::MoveAxisZ: MoveAxisZIndicator.Color() = ColorF4(0, 0, 1); break;
			case EIndicatorType::SpinRingX: SpinRingXIndicator.Color() = ColorF4(1, 0, 0); break;
			case EIndicatorType::SpinRingY: SpinRingYIndicator.Color() = ColorF4(0, 1, 0); break;
			case EIndicatorType::SpinRingZ: SpinRingZIndicator.Color() = ColorF4(0, 0, 1); break;
			default: break;
		}
	}

	MoveAxisXIndicator.Scale() = dist * 0.25f;
	MoveAxisYIndicator.Scale() = dist * 0.25f;
	MoveAxisZIndicator.Scale() = dist * 0.25f;
	SpinRingXIndicator.Scale() = dist * 0.25f;
	SpinRingYIndicator.Scale() = dist * 0.25f;
	SpinRingZIndicator.Scale() = dist * 0.25f;

	MoveAxisXIndicator.Trans().Position = Trans.Position;
	MoveAxisYIndicator.Trans().Position = Trans.Position;
	MoveAxisZIndicator.Trans().Position = Trans.Position;
	SpinRingXIndicator.Trans().Position = Trans.Position;
	SpinRingYIndicator.Trans().Position = Trans.Position;
	SpinRingZIndicator.Trans().Position = Trans.Position;
}



UserTrans3DChange::UserTrans3DChange()
	: IndicatorHovering(EIndicatorType::None)
	, ChangeType(EChangeType::None)
	, AxisX(1, 0, 0)
	, AxisY(0, 1, 0)
	, AxisZ(0, 0, 1)
{ }

bool UserTrans3DChange::TypeIsNone() const
{
	return (ChangeType == EChangeType::None);
}
void UserTrans3DChange::TypeUseNone()
{
	ChangeType = EChangeType::None;
}
void UserTrans3DChange::TypeUseL()
{
	if (IndicatorHovering == EIndicatorType::None) { return; }
	switch (IndicatorHovering)
	{
		case EIndicatorType::MoveAxisX: ChangeType = EChangeType::AxisX; break;
		case EIndicatorType::MoveAxisY: ChangeType = EChangeType::AxisY; break;
		case EIndicatorType::MoveAxisZ: ChangeType = EChangeType::AxisZ; break;
		default: ChangeType = EChangeType::None; break;
	}
	Offset = Trans.Position - IndicatorOffset;
}
void UserTrans3DChange::TypeUseR()
{
	if (IndicatorHovering == EIndicatorType::None) { return; }
	switch (IndicatorHovering)
	{
		case EIndicatorType::MoveAxisX: ChangeType = EChangeType::PlaneX; break;
		case EIndicatorType::MoveAxisY: ChangeType = EChangeType::PlaneY; break;
		case EIndicatorType::MoveAxisZ: ChangeType = EChangeType::PlaneZ; break;
		default: ChangeType = EChangeType::None; break;
	}
	Offset = Trans.Position - IndicatorOffset;
}

Trans3D UserTrans3DChange::NewTransAxis(const Ray3D & ray, const VectorF3 & axis) const
{
	Ray3D axis_ray(Trans.Position - Offset, axis);
	Ray3D_Hit axis_hit;
	Ray3D_Hit hit;
	RayApproachHit(ray, hit, axis_ray, axis_hit);
	if (hit.Interval < 0.0f) { return Trans; }
	return Trans3D(axis_hit.Pos() + Offset, Trans.Rotation);
}
Trans3D UserTrans3DChange::NewTransPlane(const Ray3D & ray, const VectorF3 & axis) const
{
	Ray3D_Hit hit = RayIntersectHit(ray, Trans.Position - Offset, axis);
	if (!hit.Is()) { return Trans; }
	return Trans3D(hit.Pos() + Offset, Trans.Rotation);
}
Trans3D UserTrans3DChange::NewTrans(const Ray3D & ray)
{
	if (ChangeType == EChangeType::None) { return Trans; }
	else if (ChangeType == EChangeType::AxisX)  { return NewTransAxis(ray, AxisX); }
	else if (ChangeType == EChangeType::AxisY)  { return NewTransAxis(ray, AxisY); }
	else if (ChangeType == EChangeType::AxisZ)  { return NewTransAxis(ray, AxisZ); }
	else if (ChangeType == EChangeType::PlaneX) { return NewTransPlane(ray, AxisX); }
	else if (ChangeType == EChangeType::PlaneY) { return NewTransPlane(ray, AxisY); }
	else if (ChangeType == EChangeType::PlaneZ) { return NewTransPlane(ray, AxisZ); }
	else { return Trans; }
}
