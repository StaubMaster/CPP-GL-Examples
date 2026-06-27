#include "UserTrans3DChange.hpp"
#include "Ray3D_Hit.hpp"



UserTrans3DChange::UserTrans3DChange()
	: HoveringType(EIndicatorType::None)
	, SelectedType(EChangeType::None)
{ }



void UserTrans3DChange::ShowIndicator()
{
	MoveAxisXIndicator.ShowFull();
	MoveAxisYIndicator.ShowFull();
	MoveAxisZIndicator.ShowFull();
	SpinRingXIndicator.ShowFull();
	SpinRingYIndicator.ShowFull();
	SpinRingZIndicator.ShowFull();
}
void UserTrans3DChange::HideIndicator()
{
	MoveAxisXIndicator.HideFull();
	MoveAxisYIndicator.HideFull();
	MoveAxisZIndicator.HideFull();
	SpinRingXIndicator.HideFull();
	SpinRingYIndicator.HideFull();
	SpinRingZIndicator.HideFull();
}



#include <iostream>
#include "ValueType/_Show.hpp"

void UserTrans3DChange::FindIndicator(const RayF3 & ray)
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
		HoveringType = hit.Index;
		HoveringOffset.Position = hit.Pos();
		VectorF3 rel = !(hit.Pos() - Trans.Position);
		VectorF3 axisX(1, 0, 0);
		VectorF3 axisY(0, 1, 0);
		VectorF3 axisZ(0, 0, 1);
		HoveringOffset.Rotation.Z0 = Angle::aTan2(axisZ.dot(axisX.cross(rel)), axisX.dot(rel));
		HoveringOffset.Rotation.X1 = Angle::aTan2(axisX.dot(axisY.cross(rel)), axisY.dot(rel));
		HoveringOffset.Rotation.Y2 = Angle::aTan2(axisY.dot(axisZ.cross(rel)), axisZ.dot(rel));
	}
	else
	{
		HoveringType = EIndicatorType::None;
		HoveringOffset = Trans3D();
	}

	UpdateIndicatorColor();
}

void UserTrans3DChange::UpdateIndicatorColor()
{
	if (HoveringType != EIndicatorType::None)
	{
		MoveAxisXIndicator.Color() = ColorF4(0.5f, 0.5f, 0.5f);
		MoveAxisYIndicator.Color() = ColorF4(0.5f, 0.5f, 0.5f);
		MoveAxisZIndicator.Color() = ColorF4(0.5f, 0.5f, 0.5f);
		SpinRingXIndicator.Color() = ColorF4(0.5f, 0.5f, 0.5f);
		SpinRingYIndicator.Color() = ColorF4(0.5f, 0.5f, 0.5f);
		SpinRingZIndicator.Color() = ColorF4(0.5f, 0.5f, 0.5f);

		switch (HoveringType)
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
	else
	{
		MoveAxisXIndicator.Color() = ColorF4(1, 0, 0);
		MoveAxisYIndicator.Color() = ColorF4(0, 1, 0);
		MoveAxisZIndicator.Color() = ColorF4(0, 0, 1);
		SpinRingXIndicator.Color() = ColorF4(1, 0, 0);
		SpinRingYIndicator.Color() = ColorF4(0, 1, 0);
		SpinRingZIndicator.Color() = ColorF4(0, 0, 1);
	}
}
void UserTrans3DChange::UpdateIndicatorScale(float scale)
{
	MoveAxisXIndicator.Scale() = scale;
	MoveAxisYIndicator.Scale() = scale;
	MoveAxisZIndicator.Scale() = scale;
	SpinRingXIndicator.Scale() = scale;
	SpinRingYIndicator.Scale() = scale;
	SpinRingZIndicator.Scale() = scale;
}
void UserTrans3DChange::UpdateIndicatorTrans(const Trans3D & trans)
{
	MoveAxisXIndicator.Trans().Position = trans.Position;
	MoveAxisYIndicator.Trans().Position = trans.Position;
	MoveAxisZIndicator.Trans().Position = trans.Position;

	SpinRingXIndicator.Trans().Position = trans.Position;
	SpinRingYIndicator.Trans().Position = trans.Position;
	SpinRingZIndicator.Trans().Position = trans.Position;

	EulerAngle3D rot;
	rot.Y2 = trans.Rotation.Y2; SpinRingYIndicator.Trans().Rotation = rot;
	rot.X1 = trans.Rotation.X1; SpinRingXIndicator.Trans().Rotation = rot;
	rot.Z0 = trans.Rotation.Z0; SpinRingZIndicator.Trans().Rotation = rot;
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

void UserTrans3DChange::UpdateIndicator(const Trans3D & trans, const View3D & view, const DisplaySize & display_size)
{
	float scale = (view.Trans.Position - trans.Position).length() * 0.25f;
	UpdateIndicatorScale(scale);
	UpdateIndicatorTrans(trans);

	(void)display_size;

//	float scale = 100.0f;
//
//	MoveAxisXIndicator.Scale() = scale;
//	MoveAxisYIndicator.Scale() = scale;
//	MoveAxisZIndicator.Scale() = scale;
//	SpinRingXIndicator.Scale() = scale;
//	SpinRingYIndicator.Scale() = scale;
//	SpinRingZIndicator.Scale() = scale;
//
//	VectorF3 pos = Project(VectorF3(), Trans, view, display_size, scale);
//
//	Trans3D trans(pos);
//
//	MoveAxisXIndicator.Trans() = trans;
//	MoveAxisYIndicator.Trans() = trans;
//	MoveAxisZIndicator.Trans() = trans;
//	SpinRingXIndicator.Trans() = trans;
//	SpinRingYIndicator.Trans() = trans;
//	SpinRingZIndicator.Trans() = trans;
}


bool UserTrans3DChange::HoveringIsNone() const
{
	return (HoveringType == EIndicatorType::None);
}

bool UserTrans3DChange::SelectedIsNone() const
{
	return (SelectedType == EChangeType::None);
}

void UserTrans3DChange::UseNone()
{
	SelectedType = EChangeType::None;
}
void UserTrans3DChange::UseL()
{
	if (HoveringType == EIndicatorType::None) { return; }
	switch (HoveringType)
	{
		case EIndicatorType::MoveAxisX: SelectedType = EChangeType::LineX; break;
		case EIndicatorType::MoveAxisY: SelectedType = EChangeType::LineY; break;
		case EIndicatorType::MoveAxisZ: SelectedType = EChangeType::LineZ; break;
		case EIndicatorType::SpinRingX: SelectedType = EChangeType::SpinX; break;
		case EIndicatorType::SpinRingY: SelectedType = EChangeType::SpinY; break;
		case EIndicatorType::SpinRingZ: SelectedType = EChangeType::SpinZ; break;
		default: SelectedType = EChangeType::None; break;
	}
	SelectedOffset.Position = Trans.Position - HoveringOffset.Position;
	SelectedOffset.Rotation = Trans.Rotation - HoveringOffset.Rotation;
}
void UserTrans3DChange::UseR()
{
	if (HoveringType == EIndicatorType::None) { return; }
	switch (HoveringType)
	{
		case EIndicatorType::MoveAxisX: SelectedType = EChangeType::PlaneX; break;
		case EIndicatorType::MoveAxisY: SelectedType = EChangeType::PlaneY; break;
		case EIndicatorType::MoveAxisZ: SelectedType = EChangeType::PlaneZ; break;
		default: SelectedType = EChangeType::None; break;
	}
	SelectedOffset.Position = Trans.Position - HoveringOffset.Position;
	SelectedOffset.Rotation = Trans.Rotation - HoveringOffset.Rotation;
}



VectorF3 UserTrans3DChange::NewPosAxis(const RayF3 & ray, const VectorF3 & axis) const
{
	RayF3 axis_ray(Trans.Position - SelectedOffset.Position, axis);
	Ray3D_Hit axis_hit;
	Ray3D_Hit hit;
	RaySkew(ray, hit, axis_ray, axis_hit);
	if (hit.Interval < 0.0f) { return Trans.Position; }
	return (axis_hit.Pos() + SelectedOffset.Position);
}
VectorF3 UserTrans3DChange::NewPosPlane(const RayF3 & ray, const VectorF3 & axis) const
{
	Ray3D_Hit hit = RayHitPlane(ray, Plane3D(Trans.Position - SelectedOffset.Position, axis));
	if (!hit.Is()) { return Trans.Position; }
	return (hit.Pos() + SelectedOffset.Position);
}
EulerAngle3D UserTrans3DChange::NewRotPlaneX(const RayF3 & ray) const
{
	EulerAngle3D euler(Angle(), Angle(), Trans.Rotation.Y2);
	VectorF3 axis0 = euler.forward(VectorF3(1, 0, 0));
	VectorF3 axis1 = euler.forward(VectorF3(0, 1, 0));
	Ray3D_Hit hit = RayHitPlane(ray, Plane3D(Trans.Position, axis0));
	if (!hit.Is()) { return Trans.Rotation; }
	VectorF3 rel = !(hit.Pos() - Trans.Position);
	Angle ang = Angle::aTan2(axis0.dot(axis1.cross(rel)), axis1.dot(rel));
	return EulerAngle3D(Trans.Rotation.Z0, ang + SelectedOffset.Rotation.X1, Trans.Rotation.Y2);
}
EulerAngle3D UserTrans3DChange::NewRotPlaneY(const RayF3 & ray) const
{
	//EulerAngle3D euler(Angle(), Angle(), Angle()); // how is this an error ?
	EulerAngle3D euler;
	VectorF3 axis0 = euler.forward(VectorF3(0, 1, 0));
	VectorF3 axis1 = euler.forward(VectorF3(0, 0, 1));
	Ray3D_Hit hit = RayHitPlane(ray, Plane3D(Trans.Position, axis0));
	if (!hit.Is()) { return Trans.Rotation; }
	VectorF3 rel = !(hit.Pos() - Trans.Position);
	Angle ang = Angle::aTan2(axis0.dot(axis1.cross(rel)), axis1.dot(rel));
	return EulerAngle3D(Trans.Rotation.Z0, Trans.Rotation.X1, ang + SelectedOffset.Rotation.Y2);
}
EulerAngle3D UserTrans3DChange::NewRotPlaneZ(const RayF3 & ray) const
{
	EulerAngle3D euler(Angle(), Trans.Rotation.X1, Trans.Rotation.Y2);
	VectorF3 axis0 = euler.forward(VectorF3(0, 0, 1));
	VectorF3 axis1 = euler.forward(VectorF3(1, 0, 0));
	Ray3D_Hit hit = RayHitPlane(ray, Plane3D(Trans.Position, axis0));
	if (!hit.Is()) { return Trans.Rotation; }
	VectorF3 rel = !(hit.Pos() - Trans.Position);
	Angle ang = Angle::aTan2(axis0.dot(axis1.cross(rel)), axis1.dot(rel));
	return EulerAngle3D(ang + SelectedOffset.Rotation.Z0, Trans.Rotation.X1, Trans.Rotation.Y2);
}
Trans3D UserTrans3DChange::NewTrans(const RayF3 & ray) const
{
	switch (SelectedType)
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
