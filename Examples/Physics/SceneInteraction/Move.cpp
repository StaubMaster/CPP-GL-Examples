#include "SceneInteraction/Move.hpp"
#include "Grid2D.hpp"



InteractionObjectMove::InteractionObjectMove()
	: SceneInteractionBase()
	, Object(Undex::Invalid())
{ }



void InteractionObjectMove::Escape(SceneInteractionData & SceneData)
{
	if (Object.IsValid())
	{
		Trans2D & now = SceneData.Manager.Objects[Object] -> ExtData.Now;
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
			Arrows[i].Clear();
		}
	}
}
void InteractionObjectMove::Start(SceneInteractionData & SceneData)
{
	if (Object.IsValid()) { return; }
	Object = SceneData.Hovering;
	if (Object.IsValid())
	{
		Trans2D & now = SceneData.Manager.Objects[Object] -> ExtData.Now;
		Origin = now.Pos;
		Offset = SceneData.Cursor - Origin;
	}
}
void InteractionObjectMove::Change(SceneInteractionData & SceneData)
{
	if (Object.IsValid())
	{
		Target = SceneData.Cursor - Offset;

		//Grid2D grid(0.1f, 15.0f);
		//Target = grid.Align(Target);
	}
}
void InteractionObjectMove::Update(SceneInteractionData & SceneData)
{
	if (Object.IsValid())
	{
		Trans2D & now = SceneData.Manager.Objects[Object] -> ExtData.Now;
		now.Pos = Target;
		if (Arrows.Is())
		{
			Trans2D & now = SceneData.Manager.Objects[Object] -> ExtData.Now;
			(Arrows[0] = ColorF4(1, 1, 1)) = Ray2D(now.Pos, Offset);
			(Arrows[1] = ColorF4(1, 1, 1)) = Line2D(Origin, now.Pos);
		}
	}
}

void InteractionObjectMove::Show()
{
	Arrows.Allocate(2);
}
