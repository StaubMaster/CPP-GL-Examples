#include "UI/Change3D/VectorF3.hpp"
#include "PolyHedra/Manager.hpp"

#include "Special/TransScaleColor3D/Display/ObjectManager.hpp"
#include "NewPolyHedra/Pallet/Manager.hpp"

#include "Ray3D_Hit.hpp"
#include "ValueType/Ray/Hit/F3Type.hpp"
#include "ValueType/Interact/3D.hpp"
#include "ValueType/NormalPlaneF3.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Parser.hpp"
#include "DirectoryInfo.hpp"



TransScaleColor3D::DisplayObject * Change3D::VectorF3::MoveAxisX_DisplayObject = nullptr;
TransScaleColor3D::DisplayObject * Change3D::VectorF3::MoveAxisY_DisplayObject = nullptr;
TransScaleColor3D::DisplayObject * Change3D::VectorF3::MoveAxisZ_DisplayObject = nullptr;



bool Change3D::VectorF3::IndicatorsIsVisible() const
{
	return IsVisible;
}
void Change3D::VectorF3::IndicatorsShow()
{
	IsVisible = true;
}
void Change3D::VectorF3::IndicatorsHide()
{
	IsVisible = false;
}

RayHitF3 Change3D::VectorF3::IndicatorsFind(const RayF3 & ray)
{
	if (!IndicatorsIsVisible()) { return RayHitF3(); }
	if (IsSelected()) { return RayHitF3(); }

	RayHitF3Type<EType> hit(EType::None);

	hit.Consider(RayHitObject(ray, *MoveAxisX_DisplayObject, MoveAxisX_Data), EType::Hovering_MoveAxisX);
	hit.Consider(RayHitObject(ray, *MoveAxisY_DisplayObject, MoveAxisY_Data), EType::Hovering_MoveAxisY);
	hit.Consider(RayHitObject(ray, *MoveAxisZ_DisplayObject, MoveAxisZ_Data), EType::Hovering_MoveAxisZ);

	if (hit.Is())
	{
		Make(hit.Data, hit.Pos());
	}
	else
	{
		MakeNone();
	}

	return hit;
}

void Change3D::VectorF3::IndicatorsUpdateColor()
{
	if (Type != EType::None)
	{
		MoveAxisX_Data.Color = ColorF4(0.5f, 0.5f, 0.5f);
		MoveAxisY_Data.Color = ColorF4(0.5f, 0.5f, 0.5f);
		MoveAxisZ_Data.Color = ColorF4(0.5f, 0.5f, 0.5f);

		switch (Type)
		{
			case EType::Hovering_MoveAxisX: MoveAxisX_Data.Color = ColorF4(1, 0, 0); break;
			case EType::Hovering_MoveAxisY: MoveAxisY_Data.Color = ColorF4(0, 1, 0); break;
			case EType::Hovering_MoveAxisZ: MoveAxisZ_Data.Color = ColorF4(0, 0, 1); break;
			default: break;
		}
	}
	else
	{
		MoveAxisX_Data.Color = ColorF4(1, 0, 0);
		MoveAxisY_Data.Color = ColorF4(0, 1, 0);
		MoveAxisZ_Data.Color = ColorF4(0, 0, 1);
	}
}
void Change3D::VectorF3::IndicatorsUpdateScale(float scale)
{
	MoveAxisX_Data.Scale = scale;
	MoveAxisY_Data.Scale = scale;
	MoveAxisZ_Data.Scale = scale;
}
void Change3D::VectorF3::IndicatorsUpdateTrans()
{
	MoveAxisX_Data.Trans.Position = Value;
	MoveAxisY_Data.Trans.Position = Value;
	MoveAxisZ_Data.Trans.Position = Value;
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



void Change3D::VectorF3::Make(EType type, ::VectorF3 offset)
{
	Type = type;
	Offset = offset;
	IndicatorsUpdateColor();
}

void Change3D::VectorF3::MakeNone()
{
	Make(EType::None, ::VectorF3());
}
void Change3D::VectorF3::MakeOther()
{
	Make(EType::Other, ::VectorF3());
}

bool Change3D::VectorF3::IsNone() const
{
	switch (Type)
	{
		case EType::None: return true;
		case EType::Other: return true;
		default: return false;
	}
}
bool Change3D::VectorF3::IsHovering() const
{
	switch (Type)
	{
		case EType::Hovering_MoveAxisX: return true;
		case EType::Hovering_MoveAxisY: return true;
		case EType::Hovering_MoveAxisZ: return true;
		default: return false;
	}
}
bool Change3D::VectorF3::IsSelected() const
{
	switch (Type)
	{
		case EType::Selected_LineX: return true;
		case EType::Selected_LineY: return true;
		case EType::Selected_LineZ: return true;
		case EType::Selected_PlaneX: return true;
		case EType::Selected_PlaneY: return true;
		case EType::Selected_PlaneZ: return true;
		default: return false;
	}
}

void Change3D::VectorF3::SelectedMakeL()
{
	if (!IndicatorsIsVisible()) { return; }
	if (!IsHovering()) { return; } // this is the same switch ?
	switch (Type)
	{
		case EType::Hovering_MoveAxisX: Type = EType::Selected_LineX; break;
		case EType::Hovering_MoveAxisY: Type = EType::Selected_LineY; break;
		case EType::Hovering_MoveAxisZ: Type = EType::Selected_LineZ; break;
		default: Type = EType::None; break;
	}
	Offset = Value - Offset;
}
void Change3D::VectorF3::SelectedMakeR()
{
	if (!IndicatorsIsVisible()) { return; }
	if (!IsHovering()) { return; } // this is the same switch ?
	switch (Type)
	{
		case EType::Hovering_MoveAxisX: Type = EType::Selected_PlaneX; break;
		case EType::Hovering_MoveAxisY: Type = EType::Selected_PlaneY; break;
		case EType::Hovering_MoveAxisZ: Type = EType::Selected_PlaneZ; break;
		default: Type = EType::None; break;
	}
	Offset = Value - Offset;
}



::VectorF3 Change3D::VectorF3::CalculateAxis(const RayF3 & ray, const ::VectorF3 & axis) const
{
	RayF3 axis_ray(Value - Offset, axis);
	RayHitF3 axis_hit;
	RayHitF3 hit;
	Interact3D::Skew(ray, hit, axis_ray, axis_hit);
	if (hit.Interval < 0.0f) { return Value; }
	return (axis_hit.Pos() + Offset);
}
::VectorF3 Change3D::VectorF3::CalculatePlane(const RayF3 & ray, const ::VectorF3 & axis) const
{
	RayHitF3 hit = Interact3D::Plane(ray, NormalPlaneF3(Value - Offset, axis));
	if (!hit.Is()) { return Value; }
	return (hit.Pos() + Offset);
}
::VectorF3 Change3D::VectorF3::Calculate(const RayF3 & ray) const
{
	::VectorF3 value = Value;
	switch (Type)
	{
		case EType::Selected_LineX:  value = CalculateAxis(ray, ::VectorF3(1, 0, 0)); break;
		case EType::Selected_LineY:  value = CalculateAxis(ray, ::VectorF3(0, 1, 0)); break;
		case EType::Selected_LineZ:  value = CalculateAxis(ray, ::VectorF3(0, 0, 1)); break;
		case EType::Selected_PlaneX: value = CalculatePlane(ray, ::VectorF3(1, 0, 0)); break;
		case EType::Selected_PlaneY: value = CalculatePlane(ray, ::VectorF3(0, 1, 0)); break;
		case EType::Selected_PlaneZ: value = CalculatePlane(ray, ::VectorF3(0, 0, 1)); break;
		default: return value;
	}
	return value;
}



void Change3D::VectorF3::Display()
{
	if (IndicatorsIsVisible())
	{
		MoveAxisX_DisplayObject -> InstancesFullPut(MoveAxisX_Data);
		MoveAxisY_DisplayObject -> InstancesFullPut(MoveAxisY_Data);
		MoveAxisZ_DisplayObject -> InstancesFullPut(MoveAxisZ_Data);
	}
}
