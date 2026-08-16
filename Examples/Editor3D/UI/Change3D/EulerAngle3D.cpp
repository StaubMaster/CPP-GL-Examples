#include "UI/Change3D/EulerAngle3D.hpp"

#include "Ray3D_Hit.hpp"
#include "ValueType/Ray/Hit/F3Type.hpp"
#include "ValueType/InteractF3.hpp"
#include "ValueType/NormalPlaneF3.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "DirectoryInfo.hpp"



void Change3D::EulerAngle3D::IndicatorsInit(const DirectoryInfo & dir)
{
	SpinRingX.Create(PolyHedra::Load(dir.File("SpinRing/RingX.polyhedra")));
	SpinRingY.Create(PolyHedra::Load(dir.File("SpinRing/RingY.polyhedra")));
	SpinRingZ.Create(PolyHedra::Load(dir.File("SpinRing/RingZ.polyhedra")));
}

void Change3D::EulerAngle3D::IndicatorsShow()
{
	SpinRingX.ShowFull();
	SpinRingY.ShowFull();
	SpinRingZ.ShowFull();
	Base::IndicatorsShow();
}
void Change3D::EulerAngle3D::IndicatorsHide()
{
	SpinRingX.HideFull();
	SpinRingY.HideFull();
	SpinRingZ.HideFull();
	Base::IndicatorsHide();
}

RayHitF3 Change3D::EulerAngle3D::IndicatorsFind(const RayF3 & ray)
{
	if (!IndicatorsIsVisible()) { return RayHitF3(); }
	if (!SelectedIsNone()) { return RayHitF3(); }

	RayHitF3Type<EIndicatorType> hit(EIndicatorType::None);

	hit.Consider(RayHitObject(ray, SpinRingX), EIndicatorType::SpinRingX);
	hit.Consider(RayHitObject(ray, SpinRingY), EIndicatorType::SpinRingY);
	hit.Consider(RayHitObject(ray, SpinRingZ), EIndicatorType::SpinRingZ);

	if (hit.Is())
	{
		HoveringType = hit.Data;
		VectorF3 rel = !(hit.Pos() - Center);
		VectorF3 axisX(1, 0, 0);
		VectorF3 axisY(0, 1, 0);
		VectorF3 axisZ(0, 0, 1);
		HoveringOffset.Z0 = Angle::aTan2(axisZ.dot(axisX.cross(rel)), axisX.dot(rel));
		HoveringOffset.X1 = Angle::aTan2(axisX.dot(axisY.cross(rel)), axisY.dot(rel));
		HoveringOffset.Y2 = Angle::aTan2(axisY.dot(axisZ.cross(rel)), axisZ.dot(rel));
		IndicatorsUpdateColor();
	}
	else
	{
		HoveringMakeNone();
	}

	return hit;
}

void Change3D::EulerAngle3D::IndicatorsUpdateColor()
{
	if (HoveringType != EIndicatorType::None)
	{
		SpinRingX.Data().Color = ColorF4(0.5f, 0.5f, 0.5f);
		SpinRingY.Data().Color = ColorF4(0.5f, 0.5f, 0.5f);
		SpinRingZ.Data().Color = ColorF4(0.5f, 0.5f, 0.5f);

		switch (HoveringType)
		{
			case EIndicatorType::SpinRingX: SpinRingX.Data().Color = ColorF4(1, 0, 0); break;
			case EIndicatorType::SpinRingY: SpinRingY.Data().Color = ColorF4(0, 1, 0); break;
			case EIndicatorType::SpinRingZ: SpinRingZ.Data().Color = ColorF4(0, 0, 1); break;
			default: break;
		}
	}
	else
	{
		SpinRingX.Data().Color = ColorF4(1, 0, 0);
		SpinRingY.Data().Color = ColorF4(0, 1, 0);
		SpinRingZ.Data().Color = ColorF4(0, 0, 1);
	}
}
void Change3D::EulerAngle3D::IndicatorsUpdateScale(float scale)
{
	SpinRingX.Data().Scale = scale;
	SpinRingY.Data().Scale = scale;
	SpinRingZ.Data().Scale = scale;
}
void Change3D::EulerAngle3D::IndicatorsUpdateTrans()
{
	SpinRingX.Data().Trans.Position = Center;
	SpinRingY.Data().Trans.Position = Center;
	SpinRingZ.Data().Trans.Position = Center;

	::EulerAngle3D rot;
	rot.Y2 = Value.Y2; SpinRingY.Data().Trans.Rotation = rot;
	rot.X1 = Value.X1; SpinRingX.Data().Trans.Rotation = rot;
	rot.Z0 = Value.Z0; SpinRingZ.Data().Trans.Rotation = rot;
}

#include "Display/DisplayPosition.hpp"
void Change3D::EulerAngle3D::IndicatorsUpdate(const View3D & view, const DisplaySize & display_size)
{
	float scale = (view.Trans.Position - Center).length() * 0.25f;
	IndicatorsUpdateScale(scale);

	(void)display_size;
}



bool Change3D::EulerAngle3D::HoveringIsNone() const
{
	return (HoveringType == EIndicatorType::None);
}
void Change3D::EulerAngle3D::HoveringMakeNone()
{
	HoveringType = EIndicatorType::None;
	HoveringOffset = ::EulerAngle3D();
	IndicatorsUpdateColor();
}
void Change3D::EulerAngle3D::HoveringMakeOther()
{
	HoveringType = EIndicatorType::Other;
	HoveringOffset = ::EulerAngle3D();
	IndicatorsUpdateColor();
}

bool Change3D::EulerAngle3D::SelectedIsNone() const
{
	return (SelectedType == EChangeType::None);
}
void Change3D::EulerAngle3D::SelectedMakeNone()
{
	SelectedType = EChangeType::None;
}

void Change3D::EulerAngle3D::SelectedMakeL()
{
	if (!IndicatorsIsVisible()) { return; }
	if (HoveringIsNone()) { return; }
	if (!SelectedIsNone()) { return; }
	switch (HoveringType)
	{
		case EIndicatorType::SpinRingX: SelectedType = EChangeType::SpinX; break;
		case EIndicatorType::SpinRingY: SelectedType = EChangeType::SpinY; break;
		case EIndicatorType::SpinRingZ: SelectedType = EChangeType::SpinZ; break;
		default: SelectedType = EChangeType::None; break;
	}
	SelectedOffset = Value - HoveringOffset;
}
void Change3D::EulerAngle3D::SelectedMakeR()
{
	if (!IndicatorsIsVisible()) { return; }
	if (HoveringIsNone()) { return; }
	if (!SelectedIsNone()) { return; }
	switch (HoveringType)
	{
		case EIndicatorType::SpinRingX: SelectedType = EChangeType::SpinX; break;
		case EIndicatorType::SpinRingY: SelectedType = EChangeType::SpinY; break;
		case EIndicatorType::SpinRingZ: SelectedType = EChangeType::SpinZ; break;
		default: SelectedType = EChangeType::None; break;
	}
	SelectedOffset = Value - HoveringOffset;
}



const ::EulerAngle3D & Change3D::EulerAngle3D::Get() const
{
	return Value;
}
void Change3D::EulerAngle3D::Set(const ::EulerAngle3D & val)
{
	Value = val;
	IndicatorsUpdateTrans();
}



::EulerAngle3D Change3D::EulerAngle3D::CalculatePlaneX(const RayF3 & ray) const
{
	::EulerAngle3D euler(Angle(), Angle(), Value.Y2);
	VectorF3 axis0 = euler.forward(VectorF3(1, 0, 0));
	VectorF3 axis1 = euler.forward(VectorF3(0, 1, 0));
	RayHitF3 hit = InteractF3::Plane(ray, NormalPlaneF3(Center, axis0));
	if (!hit.Is()) { return Value; }
	VectorF3 rel = !(hit.Pos() - Center);
	Angle ang = Angle::aTan2(axis0.dot(axis1.cross(rel)), axis1.dot(rel));
	return ::EulerAngle3D(Value.Z0, ang + SelectedOffset.X1, Value.Y2);
}
::EulerAngle3D Change3D::EulerAngle3D::CalculatePlaneY(const RayF3 & ray) const
{
	//::EulerAngle3D euler(Angle(), Angle(), Angle());
	// how is this an error ?
	//because its all empty constructors
	// which for some reason gets "optimized" into "::EulerAngle3D euler();"
	// which itself causes an error, becaues it tries to call a function called "euler"
	// even though it dosent do that for other constructors
	// probably because C interprets it like that

	::EulerAngle3D euler;
	VectorF3 axis0 = euler.forward(VectorF3(0, 1, 0));
	VectorF3 axis1 = euler.forward(VectorF3(0, 0, 1));
	RayHitF3 hit = InteractF3::Plane(ray, NormalPlaneF3(Center, axis0));
	if (!hit.Is()) { return Value; }
	VectorF3 rel = !(hit.Pos() - Center);
	Angle ang = Angle::aTan2(axis0.dot(axis1.cross(rel)), axis1.dot(rel));
	return ::EulerAngle3D(Value.Z0, Value.X1, ang + SelectedOffset.Y2);
}
::EulerAngle3D Change3D::EulerAngle3D::CalculatePlaneZ(const RayF3 & ray) const
{
	::EulerAngle3D euler(Angle(), Value.X1, Value.Y2);
	VectorF3 axis0 = euler.forward(VectorF3(0, 0, 1));
	VectorF3 axis1 = euler.forward(VectorF3(1, 0, 0));
	RayHitF3 hit = InteractF3::Plane(ray, NormalPlaneF3(Center, axis0));
	if (!hit.Is()) { return Value; }
	VectorF3 rel = !(hit.Pos() - Center);
	Angle ang = Angle::aTan2(axis0.dot(axis1.cross(rel)), axis1.dot(rel));
	return ::EulerAngle3D(ang + SelectedOffset.Z0, Value.X1, Value.Y2);
}
::EulerAngle3D Change3D::EulerAngle3D::Calculate(const RayF3 & ray) const
{
	::EulerAngle3D value = Value;
	switch (SelectedType)
	{
		case EChangeType::None: return value;
		case EChangeType::SpinX: value = CalculatePlaneX(ray); break;
		case EChangeType::SpinY: value = CalculatePlaneY(ray); break;
		case EChangeType::SpinZ: value = CalculatePlaneZ(ray); break;
		default: return value;
	}
	return value;
}

void Change3D::EulerAngle3D::RoundValue()
{
	Value = Value.round(Angle::Degrees(15));
}
void Change3D::EulerAngle3D::ChangeValue(const RayF3 & ray)
{
	Value = Calculate(ray);
	RoundValue();
	IndicatorsUpdateTrans();
}
