#include "SceneInteraction/Spin.hpp"
#include "Grid2D.hpp"



InteractionObjectSpin::InteractionObjectSpin()
	: SceneInteractionBase()
	, Object(Undex::Invalid())
{ }



void InteractionObjectSpin::Escape(SceneInteractionData & SceneData)
{
	if (Object.IsValid())
	{
		Trans2D & now = SceneData.Manager.Objects[Object] -> ExtData.Now;
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
			Arrows[i].Clear();
		}
	}
}
void InteractionObjectSpin::Start(SceneInteractionData & SceneData)
{
	Object = SceneData.Hovering;
	if (Object.IsValid())
	{
		Trans2D & now = SceneData.Manager.Objects[Object] -> ExtData.Now;
		Point2D rel = SceneData.Cursor - now.Pos;
		Origin = now.Rot;
		Offset = Angle2D::FromPoint2D(rel) - Origin;
	}
}
void InteractionObjectSpin::Change(SceneInteractionData & SceneData)
{
	if (Object.IsValid())
	{
		Trans2D & now = SceneData.Manager.Objects[Object] -> ExtData.Now;
		Point2D rel = SceneData.Cursor - now.Pos;
		Target = Offset + Angle2D::FromPoint2D(rel);

		//Grid2D grid(0.1f, 15.0f);
		//Target = grid.Align(Target);
	}
}
void InteractionObjectSpin::Update(SceneInteractionData & SceneData)
{
	if (Object.IsValid())
	{
		Trans2D & now = SceneData.Manager.Objects[Object] -> ExtData.Now;
		now.Rot = Target;
		if (Arrows.Is())
		{
			float len = (SceneData.Cursor - now.Pos).length();
			(Arrows[0] = ColorF4(1, 1, 1)) = Ray2D(now.Pos, (Origin - Offset) * Point2D(len, 0));
			(Arrows[1] = ColorF4(1, 1, 1)) = Ray2D(now.Pos, (Target - Offset) * Point2D(len, 0));
		}
	}
}

void InteractionObjectSpin::Show()
{
	Arrows.Allocate(2);
}
