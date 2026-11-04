#include "UI/Change3D/EulerAngle3D.hpp"
#include "PolyHedra/Manager.hpp"

//#include "Special/TransScaleColor3D/Logical/Data.hpp"
#include "Special/TransScaleColor3D/Display/ObjectManager.hpp"
#include "NewPolyHedra/Pallet/Manager.hpp"

#include "Ray3D_Hit.hpp"
#include "ValueType/Ray/Hit/F3Type.hpp"
#include "ValueType/Interact/3D.hpp"
#include "ValueType/NormalPlaneF3.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Parser.hpp"
#include "DirectoryInfo.hpp"



TransScaleColor3D::DisplayObject * Change3D::EulerAngle3D::SpinRingX_DisplayObject = nullptr;
TransScaleColor3D::DisplayObject * Change3D::EulerAngle3D::SpinRingY_DisplayObject = nullptr;
TransScaleColor3D::DisplayObject * Change3D::EulerAngle3D::SpinRingZ_DisplayObject = nullptr;



bool Change3D::EulerAngle3D::IndicatorsIsVisible() const
{
	return IsVisible;
}
void Change3D::EulerAngle3D::IndicatorsShow()
{
	IsVisible = true;
}
void Change3D::EulerAngle3D::IndicatorsHide()
{
	IsVisible = false;
}

RayHitF3 Change3D::EulerAngle3D::IndicatorsFind(const RayF3 & ray)
{
	if (!IndicatorsIsVisible()) { return RayHitF3(); }
	if (IsSelected()) { return RayHitF3(); }

	RayHitF3Type<EType> hit(EType::None);

	hit.Consider(RayHitObject(ray, *SpinRingX_DisplayObject, SpinRingX_Data), EType::Hovering_SpinRingX);
	hit.Consider(RayHitObject(ray, *SpinRingY_DisplayObject, SpinRingY_Data), EType::Hovering_SpinRingY);
	hit.Consider(RayHitObject(ray, *SpinRingZ_DisplayObject, SpinRingZ_Data), EType::Hovering_SpinRingZ);

	if (hit.Is())
	{
		Type = hit.Data;
		VectorF3 rel = !(hit.Pos() - Center);
		VectorF3 axisX(1, 0, 0);
		VectorF3 axisY(0, 1, 0);
		VectorF3 axisZ(0, 0, 1);
		Offset.Z0 = Angle::aTan2(axisZ.dot(axisX.cross(rel)), axisX.dot(rel));
		Offset.X1 = Angle::aTan2(axisX.dot(axisY.cross(rel)), axisY.dot(rel));
		Offset.Y2 = Angle::aTan2(axisY.dot(axisZ.cross(rel)), axisZ.dot(rel));
		IndicatorsUpdateColor();
	}
	else
	{
		MakeNone();
	}

	return hit;
}

void Change3D::EulerAngle3D::IndicatorsUpdateColor()
{
	if (Type != EType::None)
	{
		SpinRingX_Data.Color = ColorF4(0.5f, 0.5f, 0.5f);
		SpinRingY_Data.Color = ColorF4(0.5f, 0.5f, 0.5f);
		SpinRingZ_Data.Color = ColorF4(0.5f, 0.5f, 0.5f);

		switch (Type)
		{
			case EType::Hovering_SpinRingX: SpinRingX_Data.Color = ColorF4(1, 0, 0); break;
			case EType::Hovering_SpinRingY: SpinRingY_Data.Color = ColorF4(0, 1, 0); break;
			case EType::Hovering_SpinRingZ: SpinRingZ_Data.Color = ColorF4(0, 0, 1); break;
			default: break;
		}
	}
	else
	{
		SpinRingX_Data.Color = ColorF4(1, 0, 0);
		SpinRingY_Data.Color = ColorF4(0, 1, 0);
		SpinRingZ_Data.Color = ColorF4(0, 0, 1);
	}
}
void Change3D::EulerAngle3D::IndicatorsUpdateScale(float scale)
{
	SpinRingX_Data.Scale = scale;
	SpinRingY_Data.Scale = scale;
	SpinRingZ_Data.Scale = scale;
}
void Change3D::EulerAngle3D::IndicatorsUpdateTrans()
{
	SpinRingX_Data.Trans.Position = Center;
	SpinRingY_Data.Trans.Position = Center;
	SpinRingZ_Data.Trans.Position = Center;

	::EulerAngle3D rot;
	rot.Y2 = Value.Y2; SpinRingY_Data.Trans.Rotation = rot;
	rot.X1 = Value.X1; SpinRingX_Data.Trans.Rotation = rot;
	rot.Z0 = Value.Z0; SpinRingZ_Data.Trans.Rotation = rot;
}

#include "Display/DisplayPosition.hpp"
void Change3D::EulerAngle3D::IndicatorsUpdate(const View3D & view, const DisplaySize & display_size)
{
	float scale = (view.Trans.Position - Center).length() * 0.25f;
	IndicatorsUpdateScale(scale);

	(void)display_size;
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



void Change3D::EulerAngle3D::Make(EType type, ::EulerAngle3D offset)
{
	Type = type;
	Offset = offset;
	IndicatorsUpdateColor();
}

void Change3D::EulerAngle3D::MakeNone()
{
	Make(EType::None, ::EulerAngle3D());
}
void Change3D::EulerAngle3D::MakeOther()
{
	Make(EType::Other, ::EulerAngle3D());
}

bool Change3D::EulerAngle3D::IsNone() const
{
	switch (Type)
	{
		case EType::None: return true;
		case EType::Other: return true;
		default: return false;
	}
}
bool Change3D::EulerAngle3D::IsHovering() const
{
	switch (Type)
	{
		case EType::Hovering_SpinRingX: return true;
		case EType::Hovering_SpinRingY: return true;
		case EType::Hovering_SpinRingZ: return true;
		default: return false;
	}
}
bool Change3D::EulerAngle3D::IsSelected() const
{
	switch (Type)
	{
		case EType::Selected_SpinX: return true;
		case EType::Selected_SpinY: return true;
		case EType::Selected_SpinZ: return true;
		default: return false;
	}
}

void Change3D::EulerAngle3D::SelectedMakeL()
{
	if (!IndicatorsIsVisible()) { return; }
	if (!IsHovering()) { return; }
	if (IsSelected()) { return; }
	switch (Type)
	{
		case EType::Hovering_SpinRingX: Type = EType::Selected_SpinX; break;
		case EType::Hovering_SpinRingY: Type = EType::Selected_SpinY; break;
		case EType::Hovering_SpinRingZ: Type = EType::Selected_SpinZ; break;
		default: Type = EType::None; break;
	}
	Offset = Value - Offset;
}
void Change3D::EulerAngle3D::SelectedMakeR()
{
	if (!IndicatorsIsVisible()) { return; }
	if (!IsHovering()) { return; }
	if (IsSelected()) { return; }
	switch (Type)
	{
		case EType::Hovering_SpinRingX: Type = EType::Selected_SpinX; break;
		case EType::Hovering_SpinRingY: Type = EType::Selected_SpinY; break;
		case EType::Hovering_SpinRingZ: Type = EType::Selected_SpinZ; break;
		default: Type = EType::None; break;
	}
	Offset = Value - Offset;
}



::EulerAngle3D Change3D::EulerAngle3D::CalculatePlaneX(const RayF3 & ray) const
{
	::EulerAngle3D euler(Angle(), Angle(), Value.Y2);
	VectorF3 axis0 = euler.forward(VectorF3(1, 0, 0));
	VectorF3 axis1 = euler.forward(VectorF3(0, 1, 0));
	RayHitF3 hit = Interact3D::Plane(ray, NormalPlaneF3(Center, axis0));
	if (!hit.Is()) { return Value; }
	VectorF3 rel = !(hit.Pos() - Center);
	Angle ang = Angle::aTan2(axis0.dot(axis1.cross(rel)), axis1.dot(rel));
	return ::EulerAngle3D(Value.Z0, ang + Offset.X1, Value.Y2);
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
	RayHitF3 hit = Interact3D::Plane(ray, NormalPlaneF3(Center, axis0));
	if (!hit.Is()) { return Value; }
	VectorF3 rel = !(hit.Pos() - Center);
	Angle ang = Angle::aTan2(axis0.dot(axis1.cross(rel)), axis1.dot(rel));
	return ::EulerAngle3D(Value.Z0, Value.X1, ang + Offset.Y2);
}
::EulerAngle3D Change3D::EulerAngle3D::CalculatePlaneZ(const RayF3 & ray) const
{
	::EulerAngle3D euler(Angle(), Value.X1, Value.Y2);
	VectorF3 axis0 = euler.forward(VectorF3(0, 0, 1));
	VectorF3 axis1 = euler.forward(VectorF3(1, 0, 0));
	RayHitF3 hit = Interact3D::Plane(ray, NormalPlaneF3(Center, axis0));
	if (!hit.Is()) { return Value; }
	VectorF3 rel = !(hit.Pos() - Center);
	Angle ang = Angle::aTan2(axis0.dot(axis1.cross(rel)), axis1.dot(rel));
	return ::EulerAngle3D(ang + Offset.Z0, Value.X1, Value.Y2);
}
::EulerAngle3D Change3D::EulerAngle3D::Calculate(const RayF3 & ray) const
{
	::EulerAngle3D value = Value;
	switch (Type)
	{
		case EType::Selected_SpinX: value = CalculatePlaneX(ray); break;
		case EType::Selected_SpinY: value = CalculatePlaneY(ray); break;
		case EType::Selected_SpinZ: value = CalculatePlaneZ(ray); break;
		default: return value;
	}
	return value;
}



void Change3D::EulerAngle3D::Display()
{
	if (IndicatorsIsVisible())
	{
		SpinRingX_DisplayObject -> InstancesFullPut(SpinRingX_Data);
		SpinRingY_DisplayObject -> InstancesFullPut(SpinRingY_Data);
		SpinRingZ_DisplayObject -> InstancesFullPut(SpinRingZ_Data);
	}
}
