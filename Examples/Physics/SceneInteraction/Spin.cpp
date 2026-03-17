#include "SceneInteraction/Spin.hpp"



InteractionObjectSpin::InteractionObjectSpin()
	: SceneInteractionBase()
{ }

void InteractionObjectSpin::Escape(SceneInteractionData & SceneData)
{
	if (Undex.IsValid())
	{
		Trans2D & now = SceneData.Manager.Objects[Undex.Value] -> Data.Now;
		now.Rot = Origin;
		End(SceneData);
	}
}

void InteractionObjectSpin::Start(SceneInteractionData & SceneData)
{
	Undex = SceneData.Hovering;
	if (Undex.IsValid())
	{
		Trans2D & now = SceneData.Manager.Objects[Undex.Value] -> Data.Now;
		Point2D rel = SceneData.Cursor - now.Pos;
		rel = Point2D(rel.Y, rel.X);
		Origin = now.Rot;
		Offset = now.Rot - Angle2D::FromPoint2D(rel);
	}
}
void InteractionObjectSpin::Update(SceneInteractionData & SceneData)
{
	if (Undex.IsValid())
	{
		Trans2D & now = SceneData.Manager.Objects[Undex.Value] -> Data.Now;
		Point2D rel = SceneData.Cursor - now.Pos;
		rel = Point2D(rel.Y, rel.X);
		now.Rot = Offset + Angle2D::FromPoint2D(rel);
		if (Arrows.Is())
		{
			rel = Point2D(rel.Y, rel.X);
			Trans2D & now = SceneData.Manager.Objects[Undex.Value] -> Data.Now;
			Arrows[0] = Arrow2D::Inst::Data(ColorF4(1, 1, 1), 16.0f, Ray2D(now.Pos, rel));
			Arrows[1] = Arrow2D::Inst::Data(ColorF4(1, 0, 1), 16.0f, Ray2D(now.Pos, Origin * Point2D(rel.length(), 0)));
		}
	}
}

void InteractionObjectSpin::Show()
{
	Arrows.Allocate(2);
}
