#include "SceneInteraction/Spin.hpp"



InteractionObjectSpin::InteractionObjectSpin()
	: SceneInteractionBase()
	, Object(Undex::Invalid())
{ }



void InteractionObjectSpin::Escape(SceneInteractionData & SceneData)
{
	if (Object.IsValid())
	{
		Trans2D & now = SceneData.Manager.Objects[Object.Value] -> Data.Now;
		now.Rot = Origin;
		End(SceneData);
	}
}
void InteractionObjectSpin::End(SceneInteractionData & SceneData)
{
	(void)SceneData;
	if (Object.IsValid())
	{
		Object = Undex::Invalid();
		for (unsigned int i = 0; i < Arrows.Count(); i++)
		{
			Arrows[i] = Arrow2D::Inst::Data();
		}
	}
}
void InteractionObjectSpin::Start(SceneInteractionData & SceneData)
{
	Object = SceneData.Hovering;
	if (Object.IsValid())
	{
		Trans2D & now = SceneData.Manager.Objects[Object.Value] -> Data.Now;
		Point2D rel = SceneData.Cursor - now.Pos;
		rel = Point2D(rel.Y, rel.X);
		Origin = now.Rot;
		Offset = Origin - Angle2D::FromPoint2D(rel);
	}
}
void InteractionObjectSpin::Change(SceneInteractionData & SceneData)
{
	if (Object.IsValid())
	{
		Trans2D & now = SceneData.Manager.Objects[Object.Value] -> Data.Now;
		Point2D rel = SceneData.Cursor - now.Pos;
		rel = Point2D(rel.Y, rel.X); // Engine coords are backwards
		Target = Angle2D::FromPoint2D(rel);
	}
}
void InteractionObjectSpin::Update(SceneInteractionData & SceneData)
{
	if (Object.IsValid())
	{
		Trans2D & now = SceneData.Manager.Objects[Object.Value] -> Data.Now;
		now.Rot = Target + Offset;
		if (Arrows.Is())
		{
			float len = (SceneData.Cursor - now.Pos).length();
			Arrows[0] = Arrow2D::Inst::Data(ColorF4(1, 1, 1), 16.0f, Ray2D(now.Pos, (Origin - Offset) * Point2D(len, 0)));
			Arrows[1] = Arrow2D::Inst::Data(ColorF4(1, 1, 1), 16.0f, Ray2D(now.Pos, (Target) * Point2D(len, 0)));
		}
	}
}

void InteractionObjectSpin::Show()
{
	Arrows.Allocate(2);
}
