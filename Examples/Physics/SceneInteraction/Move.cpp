#include "SceneInteraction/Move.hpp"



InteractionObjectMove::InteractionObjectMove()
	: SceneInteractionBase()
{ }

void InteractionObjectMove::Escape(SceneInteractionData & SceneData)
{
	if (Undex.IsValid())
	{
		Trans2D & now = SceneData.Manager.Objects[Undex.Value] -> Data.Now;
		now.Pos = Origin;
		End(SceneData);
	}
}

void InteractionObjectMove::Start(SceneInteractionData & SceneData)
{
	if (Undex.IsValid()) { return; }
	Undex = SceneData.Hovering;
	if (Undex.IsValid())
	{
		Trans2D & now = SceneData.Manager.Objects[Undex.Value] -> Data.Now;
		Origin = now.Pos;
		Offset = SceneData.Cursor - now.Pos;
	}
}
void InteractionObjectMove::Update(SceneInteractionData & SceneData)
{
	if (Undex.IsValid())
	{
		Trans2D & now = SceneData.Manager.Objects[Undex.Value] -> Data.Now;
		now.Pos = SceneData.Cursor - Offset;
		if (Arrows.Is())
		{
			Trans2D & now = SceneData.Manager.Objects[Undex.Value] -> Data.Now;
			Arrows[0] = Arrow2D::Inst::Data(ColorF4(1, 1, 1), 16.0f, Ray2D(now.Pos, Offset));
			Arrows[1] = Arrow2D::Inst::Data(ColorF4(1, 1, 1), 16.0f, Line2D(Origin, now.Pos));
		}
	}
}

void InteractionObjectMove::Show()
{
	Arrows.Allocate(2);
}
