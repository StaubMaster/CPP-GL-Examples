#include "UserTrans3DChange.hpp"
#include "Ray3D_Hit.hpp"



UserTrans3DChange::UserTrans3DChange()
	: IndicatorHovering(EIndicatorType::None)
	, ChangeType(EChangeType::None)
	, AxisX(1, 0, 0)
	, AxisY(0, 1, 0)
	, AxisZ(0, 0, 1)
{ }



#include <iostream>
#include "ValueType/_Show.hpp"

void UserTrans3DChange::FindIndicator(const Ray3D & ray)
{
	Ray3D_Hit_Type<EIndicatorType> hit(EIndicatorType::None);

	hit.Consider(RayHitObject(ray, MoveAxisXIndicator), EIndicatorType::MoveAxisX);
	hit.Consider(RayHitObject(ray, MoveAxisYIndicator), EIndicatorType::MoveAxisY);
	hit.Consider(RayHitObject(ray, MoveAxisZIndicator), EIndicatorType::MoveAxisZ);

	hit.Consider(RayHitObject(ray, SpinRingXIndicator), EIndicatorType::SpinRingX);
	//hit.Consider(RayHitObject(ray, SpinRingYIndicator), EIndicatorType::SpinRingY);
	//hit.Consider(RayHitObject(ray, SpinRingZIndicator), EIndicatorType::SpinRingZ);

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
void UserTrans3DChange::UpdateIndicator(float scale)
{
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

	MoveAxisXIndicator.Scale() = scale * 0.25f;
	MoveAxisYIndicator.Scale() = scale * 0.25f;
	MoveAxisZIndicator.Scale() = scale * 0.25f;
	SpinRingXIndicator.Scale() = scale * 0.25f;
	SpinRingYIndicator.Scale() = scale * 0.25f;
	SpinRingZIndicator.Scale() = scale * 0.25f;

	MoveAxisXIndicator.Trans().Position = Trans.Position;
	MoveAxisYIndicator.Trans().Position = Trans.Position;
	MoveAxisZIndicator.Trans().Position = Trans.Position;

	SpinRingXIndicator.Trans().Position = Trans.Position;
	SpinRingYIndicator.Trans().Position = Trans.Position;
	SpinRingZIndicator.Trans().Position = Trans.Position;

	SpinRingXIndicator.Trans().Rotation = Trans.Rotation;
}



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
		case EIndicatorType::MoveAxisX: ChangeType = EChangeType::LineX; break;
		case EIndicatorType::MoveAxisY: ChangeType = EChangeType::LineY; break;
		case EIndicatorType::MoveAxisZ: ChangeType = EChangeType::LineZ; break;
		case EIndicatorType::SpinRingX: ChangeType = EChangeType::SpinX; break;
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



VectorF3 UserTrans3DChange::NewPosAxis(const Ray3D & ray, const VectorF3 & axis) const
{
	Ray3D axis_ray(Trans.Position - Offset, axis);
	Ray3D_Hit axis_hit;
	Ray3D_Hit hit;
	RaySkew(ray, hit, axis_ray, axis_hit);
	if (hit.Interval < 0.0f) { return Trans.Position; }
	return (axis_hit.Pos() + Offset);
}
VectorF3 UserTrans3DChange::NewPosPlane(const Ray3D & ray, const VectorF3 & axis) const
{
	Ray3D_Hit hit = RayHitPlane(ray, Plane3D(Trans.Position - Offset, axis));
	if (!hit.Is()) { return Trans.Position; }
	return (hit.Pos() + Offset);
}
EulerAngle3D UserTrans3DChange::NewRotPlaneX(const Ray3D & ray) const
{
	Ray3D_Hit hit = RayHitPlane(ray, Plane3D(Trans.Position, AxisX));
	if (!hit.Is()) { return Trans.Rotation; }
	VectorF3 rel = !(hit.Pos() - Trans.Position);
	Angle ang = Angle::aTan2(AxisX.dot(AxisY.cross(rel)), AxisY.dot(rel));
	return EulerAngle3D(Trans.Rotation.Z0, ang, Trans.Rotation.Y2);
}
Trans3D UserTrans3DChange::NewTrans(const Ray3D & ray) const
{
	switch (ChangeType)
	{
		case EChangeType::None:   return Trans;
		case EChangeType::LineX:  return Trans3D(NewPosAxis(ray, AxisX), Trans.Rotation);
		case EChangeType::LineY:  return Trans3D(NewPosAxis(ray, AxisY), Trans.Rotation);
		case EChangeType::LineZ:  return Trans3D(NewPosAxis(ray, AxisZ), Trans.Rotation);
		case EChangeType::PlaneX: return Trans3D(NewPosPlane(ray, AxisX), Trans.Rotation);
		case EChangeType::PlaneY: return Trans3D(NewPosPlane(ray, AxisY), Trans.Rotation);
		case EChangeType::PlaneZ: return Trans3D(NewPosPlane(ray, AxisZ), Trans.Rotation);
		case EChangeType::SpinX:  return Trans3D(Trans.Position, NewRotPlaneX(ray));
		default: return Trans;
	}
}
