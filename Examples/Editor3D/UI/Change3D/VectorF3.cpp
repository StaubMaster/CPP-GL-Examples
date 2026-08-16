#include "UI/Change3D/VectorF3.hpp"

#include "Ray3D_Hit.hpp"
#include "ValueType/Ray/Hit/F3Type.hpp"
#include "ValueType/InteractF3.hpp"
#include "ValueType/NormalPlaneF3.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "DirectoryInfo.hpp"



void Change3D::VectorF3::IndicatorsInit(const DirectoryInfo & dir)
{
	MoveAxisX.Create(PolyHedra::Load(dir.File("MoveAxis/AxisX.polyhedra")));
	MoveAxisY.Create(PolyHedra::Load(dir.File("MoveAxis/AxisY.polyhedra")));
	MoveAxisZ.Create(PolyHedra::Load(dir.File("MoveAxis/AxisZ.polyhedra")));
}

void Change3D::VectorF3::IndicatorsShow()
{
	MoveAxisX.ShowFull();
	MoveAxisY.ShowFull();
	MoveAxisZ.ShowFull();
	Base::IndicatorsShow();
}
void Change3D::VectorF3::IndicatorsHide()
{
	MoveAxisX.HideFull();
	MoveAxisY.HideFull();
	MoveAxisZ.HideFull();
	Base::IndicatorsHide();
}

RayHitF3 Change3D::VectorF3::IndicatorsFind(const RayF3 & ray)
{
	if (!IndicatorsIsVisible()) { return RayHitF3(); }
	if (!SelectedIsNone()) { return RayHitF3(); }

	RayHitF3Type<EIndicatorType> hit(EIndicatorType::None);

	hit.Consider(RayHitObject(ray, MoveAxisX), EIndicatorType::MoveAxisX);
	hit.Consider(RayHitObject(ray, MoveAxisY), EIndicatorType::MoveAxisY);
	hit.Consider(RayHitObject(ray, MoveAxisZ), EIndicatorType::MoveAxisZ);

	if (hit.Is())
	{
		HoveringMake(hit.Data, hit.Pos());
	}
	else
	{
		HoveringMakeNone();
	}

	return hit;
}

void Change3D::VectorF3::IndicatorsUpdateColor()
{
	if (HoveringType != EIndicatorType::None)
	{
		MoveAxisX.Data().Color = ColorF4(0.5f, 0.5f, 0.5f);
		MoveAxisY.Data().Color = ColorF4(0.5f, 0.5f, 0.5f);
		MoveAxisZ.Data().Color = ColorF4(0.5f, 0.5f, 0.5f);

		switch (HoveringType)
		{
			case EIndicatorType::MoveAxisX: MoveAxisX.Data().Color = ColorF4(1, 0, 0); break;
			case EIndicatorType::MoveAxisY: MoveAxisY.Data().Color = ColorF4(0, 1, 0); break;
			case EIndicatorType::MoveAxisZ: MoveAxisZ.Data().Color = ColorF4(0, 0, 1); break;
			default: break;
		}
	}
	else
	{
		MoveAxisX.Data().Color = ColorF4(1, 0, 0);
		MoveAxisY.Data().Color = ColorF4(0, 1, 0);
		MoveAxisZ.Data().Color = ColorF4(0, 0, 1);
	}
}
void Change3D::VectorF3::IndicatorsUpdateScale(float scale)
{
	MoveAxisX.Data().Scale = scale;
	MoveAxisY.Data().Scale = scale;
	MoveAxisZ.Data().Scale = scale;
}
void Change3D::VectorF3::IndicatorsUpdateTrans()
{
	MoveAxisX.Data().Trans.Position = Value;
	MoveAxisY.Data().Trans.Position = Value;
	MoveAxisZ.Data().Trans.Position = Value;
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

void Change3D::VectorF3::IndicatorsUpdate(const View3D & view, const DisplaySize & display_size)
{
	float scale = (view.Trans.Position - Value).length() * 0.25f;
	IndicatorsUpdateScale(scale);

	(void)display_size;
	/* Indicator Scale
		scale currently depends on distance
			Indicators are larger at the Boarder of Display, and smaller in Middle
		should have constant size on Display
	*/
}



const ::VectorF3 & Change3D::VectorF3::Get() const
{
	return Value;
}
void Change3D::VectorF3::Set(const ::VectorF3 & val)
{
	Value = val;
	IndicatorsUpdateTrans();
}

void Change3D::VectorF3::RoundValue()
{
	Value = Value.round(0.1f);
}
void Change3D::VectorF3::ChangeValue(const RayF3 & ray)
{
	Value = Calculate(ray);
	RoundValue();
	IndicatorsUpdateTrans();
}



bool Change3D::VectorF3::HoveringIsNone() const
{
	return (HoveringType == EIndicatorType::None || HoveringType == EIndicatorType::Other);
}
void Change3D::VectorF3::HoveringMakeNone()
{
	HoveringType = EIndicatorType::None;
	HoveringOffset = ::VectorF3();
	IndicatorsUpdateColor();
}
void Change3D::VectorF3::HoveringMakeOther()
{
	HoveringType = EIndicatorType::Other;
	HoveringOffset = ::VectorF3();
	IndicatorsUpdateColor();
}
void Change3D::VectorF3::HoveringMake(EIndicatorType type, ::VectorF3 offset)
{
	HoveringType = type;
	HoveringOffset = offset;
	IndicatorsUpdateColor();
}



bool Change3D::VectorF3::SelectedIsNone() const
{
	return (SelectedType == EChangeType::None);
}
void Change3D::VectorF3::SelectedMakeNone()
{
	SelectedType = EChangeType::None;
}

void Change3D::VectorF3::SelectedMakeL()
{
	if (!IndicatorsIsVisible()) { return; }
	if (HoveringIsNone()) { return; }
	if (!SelectedIsNone()) { return; }
	switch (HoveringType)
	{
		case EIndicatorType::MoveAxisX: SelectedType = EChangeType::LineX; break;
		case EIndicatorType::MoveAxisY: SelectedType = EChangeType::LineY; break;
		case EIndicatorType::MoveAxisZ: SelectedType = EChangeType::LineZ; break;
		default: SelectedType = EChangeType::None; break;
	}
	SelectedOffset = Value - HoveringOffset;
}
void Change3D::VectorF3::SelectedMakeR()
{
	if (!IndicatorsIsVisible()) { return; }
	if (HoveringIsNone()) { return; }
	if (!SelectedIsNone()) { return; }
	switch (HoveringType)
	{
		case EIndicatorType::MoveAxisX: SelectedType = EChangeType::PlaneX; break;
		case EIndicatorType::MoveAxisY: SelectedType = EChangeType::PlaneY; break;
		case EIndicatorType::MoveAxisZ: SelectedType = EChangeType::PlaneZ; break;
		default: SelectedType = EChangeType::None; break;
	}
	SelectedOffset = Value - HoveringOffset;
}



::VectorF3 Change3D::VectorF3::CalculateAxis(const RayF3 & ray, const ::VectorF3 & axis) const
{
	RayF3 axis_ray(Value - SelectedOffset, axis);
	RayHitF3 axis_hit;
	RayHitF3 hit;
	InteractF3::Skew(ray, hit, axis_ray, axis_hit);
	if (hit.Interval < 0.0f) { return Value; }
	return (axis_hit.Pos() + SelectedOffset);
}
::VectorF3 Change3D::VectorF3::CalculatePlane(const RayF3 & ray, const ::VectorF3 & axis) const
{
	RayHitF3 hit = InteractF3::Plane(ray, NormalPlaneF3(Value - SelectedOffset, axis));
	if (!hit.Is()) { return Value; }
	return (hit.Pos() + SelectedOffset);
}
::VectorF3 Change3D::VectorF3::Calculate(const RayF3 & ray) const
{
	::VectorF3 value = Value;
	switch (SelectedType)
	{
		case EChangeType::None: return value;
		case EChangeType::LineX:  value = CalculateAxis(ray, ::VectorF3(1, 0, 0)); break;
		case EChangeType::LineY:  value = CalculateAxis(ray, ::VectorF3(0, 1, 0)); break;
		case EChangeType::LineZ:  value = CalculateAxis(ray, ::VectorF3(0, 0, 1)); break;
		case EChangeType::PlaneX: value = CalculatePlane(ray, ::VectorF3(1, 0, 0)); break;
		case EChangeType::PlaneY: value = CalculatePlane(ray, ::VectorF3(0, 1, 0)); break;
		case EChangeType::PlaneZ: value = CalculatePlane(ray, ::VectorF3(0, 0, 1)); break;
		default: return value;
	}
	return value;
}
