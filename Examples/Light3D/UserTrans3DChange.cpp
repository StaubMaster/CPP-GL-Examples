#include "UserTrans3DChange.hpp"
#include "Ray3D_Hit.hpp"



UserTrans3DChange::UserTrans3DChange()
	: IndicatorHovering(EIndicatorType::None)
	, ChangeType(EChangeType::None)
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
	hit.Consider(RayHitObject(ray, SpinRingYIndicator), EIndicatorType::SpinRingY);
	hit.Consider(RayHitObject(ray, SpinRingZIndicator), EIndicatorType::SpinRingZ);

	if (hit.Is())
	{
		IndicatorHovering = hit.Index;
		IndicatorOffset.Position = hit.Pos();
		VectorF3 rel = !(hit.Pos() - Trans.Position);
		{
			VectorF3 axis0(0, 0, 1);
			VectorF3 axis1(1, 0, 0);
			IndicatorOffset.Rotation.Z0 = Angle::aTan2(axis0.dot(axis1.cross(rel)), axis1.dot(rel));
		}
		{
			VectorF3 axis0(1, 0, 0);
			VectorF3 axis1(0, 1, 0);
			IndicatorOffset.Rotation.X1 = Angle::aTan2(axis0.dot(axis1.cross(rel)), axis1.dot(rel));
		}
		{
			VectorF3 axis0(0, 1, 0);
			VectorF3 axis1(0, 0, 1);
			IndicatorOffset.Rotation.Y2 = Angle::aTan2(axis0.dot(axis1.cross(rel)), axis1.dot(rel));
		}
	}
	else
	{
		IndicatorHovering = EIndicatorType::None;
		IndicatorOffset = Trans3D();
	}
}



#include "Display/DisplayPosition.hpp"
/*static VectorF3 Project(
	VectorF3 pos,
	const Trans3D & trans,
	const View3D & view,
	const DisplaySize & display_size,
	float scale
)
{
	pos = trans.forward(pos);
	pos = view.Trans.reverse(pos);

	float s = 1.0f / (view.FOV * 0.5).Tan();

	float w = pos.Z;

	pos.X = pos.X * s;
	pos.Y = pos.Y * s;
	pos.Z = pos.Z;

	pos.X = pos.X * display_size.Ratio.Value.X;
	pos.Y = pos.Y * display_size.Ratio.Value.Y;

	pos = pos / w;

	pos.X = pos.X * (display_size.Buffer.Half.X / scale);
	pos.Y = pos.Y * (display_size.Buffer.Half.Y / scale);

	return pos;
}*/



void UserTrans3DChange::UpdateIndicator(const View3D & view, const DisplaySize & display_size)
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

	float scale = (view.Trans.Position - Trans.Position).length();

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

	SpinRingXIndicator.Trans().Rotation = EulerAngle3D(          Angle(), Trans.Rotation.X1, Trans.Rotation.Y2);
	SpinRingYIndicator.Trans().Rotation = EulerAngle3D(          Angle(),           Angle(), Trans.Rotation.Y2);
	SpinRingZIndicator.Trans().Rotation = EulerAngle3D(Trans.Rotation.Z0, Trans.Rotation.X1, Trans.Rotation.Y2);

	(void)display_size;

	/*float scale = 100.0f;

	MoveAxisXIndicator.Scale() = scale;
	MoveAxisYIndicator.Scale() = scale;
	MoveAxisZIndicator.Scale() = scale;
	SpinRingXIndicator.Scale() = scale;
	SpinRingYIndicator.Scale() = scale;
	SpinRingZIndicator.Scale() = scale;

	VectorF3 pos = Project(VectorF3(), Trans, view, display_size, scale);

	Trans3D trans(pos);

	MoveAxisXIndicator.Trans() = trans;
	MoveAxisYIndicator.Trans() = trans;
	MoveAxisZIndicator.Trans() = trans;
	SpinRingXIndicator.Trans() = trans;
	SpinRingYIndicator.Trans() = trans;
	SpinRingZIndicator.Trans() = trans;
	*/
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
		case EIndicatorType::SpinRingY: ChangeType = EChangeType::SpinY; break;
		case EIndicatorType::SpinRingZ: ChangeType = EChangeType::SpinZ; break;
		default: ChangeType = EChangeType::None; break;
	}
	Offset.Position = Trans.Position - IndicatorOffset.Position;
	Offset.Rotation = Trans.Rotation - IndicatorOffset.Rotation;
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
	Offset.Position = Trans.Position - IndicatorOffset.Position;
	Offset.Rotation = Trans.Rotation - IndicatorOffset.Rotation;
}



VectorF3 UserTrans3DChange::NewPosAxis(const Ray3D & ray, const VectorF3 & axis) const
{
	Ray3D axis_ray(Trans.Position - Offset.Position, axis);
	Ray3D_Hit axis_hit;
	Ray3D_Hit hit;
	RaySkew(ray, hit, axis_ray, axis_hit);
	if (hit.Interval < 0.0f) { return Trans.Position; }
	return (axis_hit.Pos() + Offset.Position);
}
VectorF3 UserTrans3DChange::NewPosPlane(const Ray3D & ray, const VectorF3 & axis) const
{
	Ray3D_Hit hit = RayHitPlane(ray, Plane3D(Trans.Position - Offset.Position, axis));
	if (!hit.Is()) { return Trans.Position; }
	return (hit.Pos() + Offset.Position);
}
EulerAngle3D UserTrans3DChange::NewRotPlaneX(const Ray3D & ray) const
{
	EulerAngle3D euler(Angle(), Angle(), Trans.Rotation.Y2);
	VectorF3 axis0 = euler.forward(VectorF3(1, 0, 0));
	VectorF3 axis1 = euler.forward(VectorF3(0, 1, 0));
	Ray3D_Hit hit = RayHitPlane(ray, Plane3D(Trans.Position, axis0));
	if (!hit.Is()) { return Trans.Rotation; }
	VectorF3 rel = !(hit.Pos() - Trans.Position);
	Angle ang = Angle::aTan2(axis0.dot(axis1.cross(rel)), axis1.dot(rel));
	return EulerAngle3D(Trans.Rotation.Z0, ang + Offset.Rotation.X1, Trans.Rotation.Y2);
}
EulerAngle3D UserTrans3DChange::NewRotPlaneY(const Ray3D & ray) const
{
	//EulerAngle3D euler(Angle(), Angle(), Angle()); // how is this an error ?
	EulerAngle3D euler;
	VectorF3 axis0 = euler.forward(VectorF3(0, 1, 0));
	VectorF3 axis1 = euler.forward(VectorF3(0, 0, 1));
	Ray3D_Hit hit = RayHitPlane(ray, Plane3D(Trans.Position, axis0));
	if (!hit.Is()) { return Trans.Rotation; }
	VectorF3 rel = !(hit.Pos() - Trans.Position);
	Angle ang = Angle::aTan2(axis0.dot(axis1.cross(rel)), axis1.dot(rel));
	return EulerAngle3D(Trans.Rotation.Z0, Trans.Rotation.X1, ang + Offset.Rotation.Y2);
}
EulerAngle3D UserTrans3DChange::NewRotPlaneZ(const Ray3D & ray) const
{
	EulerAngle3D euler(Angle(), Trans.Rotation.X1, Trans.Rotation.Y2);
	VectorF3 axis0 = euler.forward(VectorF3(0, 0, 1));
	VectorF3 axis1 = euler.forward(VectorF3(1, 0, 0));
	Ray3D_Hit hit = RayHitPlane(ray, Plane3D(Trans.Position, axis0));
	if (!hit.Is()) { return Trans.Rotation; }
	VectorF3 rel = !(hit.Pos() - Trans.Position);
	Angle ang = Angle::aTan2(axis0.dot(axis1.cross(rel)), axis1.dot(rel));
	return EulerAngle3D(ang + Offset.Rotation.Z0, Trans.Rotation.X1, Trans.Rotation.Y2);
}
Trans3D UserTrans3DChange::NewTrans(const Ray3D & ray) const
{
	switch (ChangeType)
	{
		case EChangeType::None:   return Trans;
		case EChangeType::LineX:  return Trans3D(NewPosAxis(ray, VectorF3(1, 0, 0)), Trans.Rotation);
		case EChangeType::LineY:  return Trans3D(NewPosAxis(ray, VectorF3(0, 1, 0)), Trans.Rotation);
		case EChangeType::LineZ:  return Trans3D(NewPosAxis(ray, VectorF3(0, 0, 1)), Trans.Rotation);
		case EChangeType::PlaneX: return Trans3D(NewPosPlane(ray, VectorF3(1, 0, 0)), Trans.Rotation);
		case EChangeType::PlaneY: return Trans3D(NewPosPlane(ray, VectorF3(0, 1, 0)), Trans.Rotation);
		case EChangeType::PlaneZ: return Trans3D(NewPosPlane(ray, VectorF3(0, 0, 1)), Trans.Rotation);
		case EChangeType::SpinX:  return Trans3D(Trans.Position, NewRotPlaneX(ray));
		case EChangeType::SpinY:  return Trans3D(Trans.Position, NewRotPlaneY(ray));
		case EChangeType::SpinZ:  return Trans3D(Trans.Position, NewRotPlaneZ(ray));
		default: return Trans;
	}
}
