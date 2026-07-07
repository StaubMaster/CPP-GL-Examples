#include "UserTrans3DChange.hpp"
#include "Ray3D_Hit.hpp"
#include "ValueType/Ray/Hit/F3Type.hpp"
#include "ValueType/InteractF3.hpp"
#include "ValueType/NormalPlaneF3.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "DirectoryInfo.hpp"



UserTrans3DChange::UserTrans3DChange()
	: HoveringType(EIndicatorType::None)
	, SelectedType(EChangeType::None)
{ }



void UserTrans3DChange::IndicatorsInit(const DirectoryInfo & dir)
{
	MoveAxisX.Create(PolyHedra::Load(dir.File("MoveAxis/AxisX.polyhedra")));
	MoveAxisY.Create(PolyHedra::Load(dir.File("MoveAxis/AxisY.polyhedra")));
	MoveAxisZ.Create(PolyHedra::Load(dir.File("MoveAxis/AxisZ.polyhedra")));
	SpinRingX.Create(PolyHedra::Load(dir.File("SpinRing/RingX.polyhedra")));
	SpinRingY.Create(PolyHedra::Load(dir.File("SpinRing/RingY.polyhedra")));
	SpinRingZ.Create(PolyHedra::Load(dir.File("SpinRing/RingZ.polyhedra")));
}

bool UserTrans3DChange::IndicatorsIsVisible() const
{
	return IsVisible;
}
void UserTrans3DChange::IndicatorsShow()
{
	IsVisible = true;
	MoveAxisX.ShowFull();
	MoveAxisY.ShowFull();
	MoveAxisZ.ShowFull();
	SpinRingX.ShowFull();
	SpinRingY.ShowFull();
	SpinRingZ.ShowFull();
}
void UserTrans3DChange::IndicatorsHide()
{
	IsVisible = false;
	MoveAxisX.HideFull();
	MoveAxisY.HideFull();
	MoveAxisZ.HideFull();
	SpinRingX.HideFull();
	SpinRingY.HideFull();
	SpinRingZ.HideFull();
}

void UserTrans3DChange::IndicatorsFind(const RayF3 & ray)
{
	if (!IsVisible) { return; }
	if (!SelectedIsNone()) { return; }

	RayHitF3Type<EIndicatorType> hit(EIndicatorType::None);

	hit.Consider(RayHitObject1(ray, MoveAxisX), EIndicatorType::MoveAxisX);
	hit.Consider(RayHitObject1(ray, MoveAxisY), EIndicatorType::MoveAxisY);
	hit.Consider(RayHitObject1(ray, MoveAxisZ), EIndicatorType::MoveAxisZ);

	hit.Consider(RayHitObject1(ray, SpinRingX), EIndicatorType::SpinRingX);
	hit.Consider(RayHitObject1(ray, SpinRingY), EIndicatorType::SpinRingY);
	hit.Consider(RayHitObject1(ray, SpinRingZ), EIndicatorType::SpinRingZ);

	if (hit.Is())
	{
		HoveringType = hit.Data;
		HoveringOffset.Position = hit.Pos();
		VectorF3 rel = !(hit.Pos() - Trans.Position);
		VectorF3 axisX(1, 0, 0);
		VectorF3 axisY(0, 1, 0);
		VectorF3 axisZ(0, 0, 1);
		HoveringOffset.Rotation.Z0 = Angle::aTan2(axisZ.dot(axisX.cross(rel)), axisX.dot(rel));
		HoveringOffset.Rotation.X1 = Angle::aTan2(axisX.dot(axisY.cross(rel)), axisY.dot(rel));
		HoveringOffset.Rotation.Y2 = Angle::aTan2(axisY.dot(axisZ.cross(rel)), axisZ.dot(rel));
		IndicatorsUpdateColor();
	}
	else
	{
		HoveringMakeNone();
	}
}

void UserTrans3DChange::IndicatorsUpdateColor()
{
	if (HoveringType != EIndicatorType::None)
	{
		MoveAxisX.Data().Color = ColorF4(0.5f, 0.5f, 0.5f);
		MoveAxisY.Data().Color = ColorF4(0.5f, 0.5f, 0.5f);
		MoveAxisZ.Data().Color = ColorF4(0.5f, 0.5f, 0.5f);
		SpinRingX.Data().Color = ColorF4(0.5f, 0.5f, 0.5f);
		SpinRingY.Data().Color = ColorF4(0.5f, 0.5f, 0.5f);
		SpinRingZ.Data().Color = ColorF4(0.5f, 0.5f, 0.5f);

		switch (HoveringType)
		{
			case EIndicatorType::MoveAxisX: MoveAxisX.Data().Color = ColorF4(1, 0, 0); break;
			case EIndicatorType::MoveAxisY: MoveAxisY.Data().Color = ColorF4(0, 1, 0); break;
			case EIndicatorType::MoveAxisZ: MoveAxisZ.Data().Color = ColorF4(0, 0, 1); break;
			case EIndicatorType::SpinRingX: SpinRingX.Data().Color = ColorF4(1, 0, 0); break;
			case EIndicatorType::SpinRingY: SpinRingY.Data().Color = ColorF4(0, 1, 0); break;
			case EIndicatorType::SpinRingZ: SpinRingZ.Data().Color = ColorF4(0, 0, 1); break;
			default: break;
		}
	}
	else
	{
		MoveAxisX.Data().Color = ColorF4(1, 0, 0);
		MoveAxisY.Data().Color = ColorF4(0, 1, 0);
		MoveAxisZ.Data().Color = ColorF4(0, 0, 1);
		SpinRingX.Data().Color = ColorF4(1, 0, 0);
		SpinRingY.Data().Color = ColorF4(0, 1, 0);
		SpinRingZ.Data().Color = ColorF4(0, 0, 1);
	}
}
void UserTrans3DChange::IndicatorsUpdateScale(float scale)
{
	MoveAxisX.Data().Scale = scale;
	MoveAxisY.Data().Scale = scale;
	MoveAxisZ.Data().Scale = scale;
	SpinRingX.Data().Scale = scale;
	SpinRingY.Data().Scale = scale;
	SpinRingZ.Data().Scale = scale;
}
void UserTrans3DChange::IndicatorsUpdateTrans()
{
	MoveAxisX.Data().Trans.Position = Trans.Position;
	MoveAxisY.Data().Trans.Position = Trans.Position;
	MoveAxisZ.Data().Trans.Position = Trans.Position;

	SpinRingX.Data().Trans.Position = Trans.Position;
	SpinRingY.Data().Trans.Position = Trans.Position;
	SpinRingZ.Data().Trans.Position = Trans.Position;

	EulerAngle3D rot;
	rot.Y2 = Trans.Rotation.Y2; SpinRingY.Data().Trans.Rotation = rot;
	rot.X1 = Trans.Rotation.X1; SpinRingX.Data().Trans.Rotation = rot;
	rot.Z0 = Trans.Rotation.Z0; SpinRingZ.Data().Trans.Rotation = rot;
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

void UserTrans3DChange::IndicatorsUpdate(const View3D & view, const DisplaySize & display_size)
{
	float scale = (view.Trans.Position - Trans.Position).length() * 0.25f;
	IndicatorsUpdateScale(scale);

	(void)display_size;

//	float scale = 100.0f;
//
//	MoveAxisX.Data().Scale = scale;
//	MoveAxisY.Data().Scale = scale;
//	MoveAxisZ.Data().Scale = scale;
//	SpinRingX.Data().Scale = scale;
//	SpinRingY.Data().Scale = scale;
//	SpinRingZ.Data().Scale = scale;
//
//	VectorF3 pos = Project(VectorF3(), Trans, view, display_size, scale);
//
//	Trans3D trans(pos);
//
//	MoveAxisX.Data().Trans = trans;
//	MoveAxisY.Data().Trans = trans;
//	MoveAxisZ.Data().Trans = trans;
//	SpinRingX.Data().Trans = trans;
//	SpinRingY.Data().Trans = trans;
//	SpinRingZ.Data().Trans = trans;
}



void UserTrans3DChange::HoveringMakeNone()
{
	HoveringType = EIndicatorType::None;
	HoveringOffset = Trans3D();
	IndicatorsUpdateColor();
}
bool UserTrans3DChange::HoveringIsNone() const
{
	return (HoveringType == EIndicatorType::None);
}

void UserTrans3DChange::SelectedMakeNone()
{
	SelectedType = EChangeType::None;
}
bool UserTrans3DChange::SelectedIsNone() const
{
	return (SelectedType == EChangeType::None);
}

void UserTrans3DChange::SelectedMakeL()
{
	if (!IsVisible) { return; }
	if (HoveringIsNone()) { return; }
	if (!SelectedIsNone()) { return; }
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
void UserTrans3DChange::SelectedMakeR()
{
	if (!IsVisible) { return; }
	if (HoveringIsNone()) { return; }
	if (!SelectedIsNone()) { return; }
	switch (HoveringType)
	{
		case EIndicatorType::MoveAxisX: SelectedType = EChangeType::PlaneX; break;
		case EIndicatorType::MoveAxisY: SelectedType = EChangeType::PlaneY; break;
		case EIndicatorType::MoveAxisZ: SelectedType = EChangeType::PlaneZ; break;
		case EIndicatorType::SpinRingX: SelectedType = EChangeType::SpinX; break;
		case EIndicatorType::SpinRingY: SelectedType = EChangeType::SpinY; break;
		case EIndicatorType::SpinRingZ: SelectedType = EChangeType::SpinZ; break;
		default: SelectedType = EChangeType::None; break;
	}
	SelectedOffset.Position = Trans.Position - HoveringOffset.Position;
	SelectedOffset.Rotation = Trans.Rotation - HoveringOffset.Rotation;
}



bool UserTrans3DChange::IsIdle() const
{
	return (
		HoveringIsNone() &&
		SelectedIsNone()
	);
}



Trans3D UserTrans3DChange::GetTrans() const
{
	return Trans;
}
void UserTrans3DChange::SetTrans(Trans3D trans)
{
	Trans = trans;
	IndicatorsUpdateTrans();
}



VectorF3 UserTrans3DChange::CalcPosAxis(const RayF3 & ray, const VectorF3 & axis) const
{
	RayF3 axis_ray(Trans.Position - SelectedOffset.Position, axis);
	RayHitF3 axis_hit;
	RayHitF3 hit;
	InteractF3::Skew(ray, hit, axis_ray, axis_hit);
	if (hit.Interval < 0.0f) { return Trans.Position; }
	return (axis_hit.Pos() + SelectedOffset.Position);
}
VectorF3 UserTrans3DChange::CalcPosPlane(const RayF3 & ray, const VectorF3 & axis) const
{
	RayHitF3 hit = InteractF3::Plane(ray, NormalPlaneF3(Trans.Position - SelectedOffset.Position, axis));
	if (!hit.Is()) { return Trans.Position; }
	return (hit.Pos() + SelectedOffset.Position);
}
EulerAngle3D UserTrans3DChange::CalcRotPlaneX(const RayF3 & ray) const
{
	EulerAngle3D euler(Angle(), Angle(), Trans.Rotation.Y2);
	VectorF3 axis0 = euler.forward(VectorF3(1, 0, 0));
	VectorF3 axis1 = euler.forward(VectorF3(0, 1, 0));
	RayHitF3 hit = InteractF3::Plane(ray, NormalPlaneF3(Trans.Position, axis0));
	if (!hit.Is()) { return Trans.Rotation; }
	VectorF3 rel = !(hit.Pos() - Trans.Position);
	Angle ang = Angle::aTan2(axis0.dot(axis1.cross(rel)), axis1.dot(rel));
	return EulerAngle3D(Trans.Rotation.Z0, ang + SelectedOffset.Rotation.X1, Trans.Rotation.Y2);
}
EulerAngle3D UserTrans3DChange::CalcRotPlaneY(const RayF3 & ray) const
{
	//EulerAngle3D euler(Angle(), Angle(), Angle()); // how is this an error ?
	EulerAngle3D euler;
	VectorF3 axis0 = euler.forward(VectorF3(0, 1, 0));
	VectorF3 axis1 = euler.forward(VectorF3(0, 0, 1));
	RayHitF3 hit = InteractF3::Plane(ray, NormalPlaneF3(Trans.Position, axis0));
	if (!hit.Is()) { return Trans.Rotation; }
	VectorF3 rel = !(hit.Pos() - Trans.Position);
	Angle ang = Angle::aTan2(axis0.dot(axis1.cross(rel)), axis1.dot(rel));
	return EulerAngle3D(Trans.Rotation.Z0, Trans.Rotation.X1, ang + SelectedOffset.Rotation.Y2);
}
EulerAngle3D UserTrans3DChange::CalcRotPlaneZ(const RayF3 & ray) const
{
	EulerAngle3D euler(Angle(), Trans.Rotation.X1, Trans.Rotation.Y2);
	VectorF3 axis0 = euler.forward(VectorF3(0, 0, 1));
	VectorF3 axis1 = euler.forward(VectorF3(1, 0, 0));
	RayHitF3 hit = InteractF3::Plane(ray, NormalPlaneF3(Trans.Position, axis0));
	if (!hit.Is()) { return Trans.Rotation; }
	VectorF3 rel = !(hit.Pos() - Trans.Position);
	Angle ang = Angle::aTan2(axis0.dot(axis1.cross(rel)), axis1.dot(rel));
	return EulerAngle3D(ang + SelectedOffset.Rotation.Z0, Trans.Rotation.X1, Trans.Rotation.Y2);
}
Trans3D UserTrans3DChange::CalcTrans(const RayF3 & ray) const
{
	Trans3D trans = Trans;
	switch (SelectedType)
	{
		case EChangeType::None: return Trans;
		case EChangeType::LineX:  trans.Position = CalcPosAxis(ray, VectorF3(1, 0, 0)); break;
		case EChangeType::LineY:  trans.Position = CalcPosAxis(ray, VectorF3(0, 1, 0)); break;
		case EChangeType::LineZ:  trans.Position = CalcPosAxis(ray, VectorF3(0, 0, 1)); break;
		case EChangeType::PlaneX: trans.Position = CalcPosPlane(ray, VectorF3(1, 0, 0)); break;
		case EChangeType::PlaneY: trans.Position = CalcPosPlane(ray, VectorF3(0, 1, 0)); break;
		case EChangeType::PlaneZ: trans.Position = CalcPosPlane(ray, VectorF3(0, 0, 1)); break;
		case EChangeType::SpinX:  trans.Rotation = CalcRotPlaneX(ray); break;
		case EChangeType::SpinY:  trans.Rotation = CalcRotPlaneY(ray); break;
		case EChangeType::SpinZ:  trans.Rotation = CalcRotPlaneZ(ray); break;
		default: return Trans;
	}
	return trans;
}

void UserTrans3DChange::NewTrans(const RayF3 & ray)
{
	Trans = CalcTrans(ray);
	Trans.Position = Trans.Position.round(0.1f);
	Trans.Rotation = Trans.Rotation.round(Angle::Degrees(15));
	IndicatorsUpdateTrans();
}
