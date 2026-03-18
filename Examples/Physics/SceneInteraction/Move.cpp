#include "SceneInteraction/Move.hpp"



InteractionObjectMove::InteractionObjectMove()
	: SceneInteractionBase()
	, Object(Undex::Invalid())
{ }



void InteractionObjectMove::Escape(SceneInteractionData & SceneData)
{
	if (Object.IsValid())
	{
		Trans2D & now = SceneData.Manager.Objects[Object.Value] -> Data.Now;
		now.Pos = Origin;
		End(SceneData);
	}
}
void InteractionObjectMove::End(SceneInteractionData & SceneData)
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
void InteractionObjectMove::Start(SceneInteractionData & SceneData)
{
	if (Object.IsValid()) { return; }
	Object = SceneData.Hovering;
	if (Object.IsValid())
	{
		Trans2D & now = SceneData.Manager.Objects[Object.Value] -> Data.Now;
		Origin = now.Pos;
		Offset = SceneData.Cursor - now.Pos;
	}
}
void InteractionObjectMove::Change(SceneInteractionData & SceneData)
{
	if (Object.IsValid())
	{
		Target = SceneData.Cursor - Offset;
	}
}
void InteractionObjectMove::Update(SceneInteractionData & SceneData)
{
	if (Object.IsValid())
	{
		Trans2D & now = SceneData.Manager.Objects[Object.Value] -> Data.Now;
		now.Pos = Target;
		if (Arrows.Is())
		{
			Trans2D & now = SceneData.Manager.Objects[Object.Value] -> Data.Now;
			Arrows[0] = Arrow2D::Inst::Data(ColorF4(1, 1, 1), 16.0f, Ray2D(now.Pos, Offset));
			Arrows[1] = Arrow2D::Inst::Data(ColorF4(1, 1, 1), 16.0f, Line2D(Origin, now.Pos));
		}
	}
}

void InteractionObjectMove::Show()
{
	Arrows.Allocate(2);
}
