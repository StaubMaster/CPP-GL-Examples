#include "SceneInteraction/Force.hpp"
#include "Arrow2D/RankLengths.hpp"
#include "Physics2D/Collision.hpp"



InteractionObjectDrag::InteractionObjectDrag()
	: SceneInteractionBase()
	, Object(Undex::Invalid())
{ }



void InteractionObjectDrag::Escape(SceneInteractionData & SceneData)
{
	(void)SceneData;
}
void InteractionObjectDrag::End(SceneInteractionData & SceneData)
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
void InteractionObjectDrag::Start(SceneInteractionData & SceneData)
{
	Object = SceneData.Hovering;
	if (Object.IsValid())
	{
		Offset = SceneData.Manager.Objects[Object] -> RelativePositionOf(SceneData.Cursor);
	}
}
void InteractionObjectDrag::Change(SceneInteractionData & SceneData)
{
	if (Object.IsValid())
	{
		Target = SceneData.Cursor;
	}
}
void InteractionObjectDrag::Update(SceneInteractionData & SceneData)
{
	if (Object.IsValid())
	{
		Ray2D drag;
		drag.Pos = SceneData.Manager.Objects[Object] -> AbsolutePositionOf(Offset);
		drag.Dir = Target - drag.Pos;

		Physics2D::ObjectDragForceData data = Physics2D::ApplyDragForce(SceneData.FrameTime.Delta, *(SceneData.Manager.Objects[Object]), drag, 10.0f, SceneData.IsSimulating);

		if (Arrows.Is())
		{
			Arrows[0] = Arrow2D::Inst::Data(ColorF4(1.0f, 1.0f, 1.0f), 16.0f, data.Drag);
			Arrows[1] = Arrow2D::Inst::Data(ColorF4(0.0f, 0.0f, 0.0f), 16.0f, data.Contact);

			if (SceneData.Selected == Object)
			{
				Arrows[2] = Arrow2D::Inst::Data(ColorF4(1.0f, 0.5f, 0.0f), 16.0f, data.Force);
				Arrows[3] = Arrow2D::Inst::Data(ColorF4(1.0f, 0.5f, 0.0f), 16.0f, data.ForcePos);
				Arrows[4] = Arrow2D::Inst::Data(ColorF4(1.0f, 0.5f, 0.0f), 16.0f, data.ForceRot);
				
				Arrows[5] = Arrow2D::Inst::Data(ColorF4(0.0f, 0.5f, 1.0f), 16.0f, data.ChangeRot);
				Arrows[6] = Arrow2D::Inst::Data(ColorF4(0.0f, 0.5f, 1.0f), 16.0f, data.ChangePos);
			}
			else
			{
				for (unsigned int i = 2; i < Arrows.Count(); i++)
				{
					Arrows[i] = Arrow2D::Inst::Data();
				}
			}
		}
	}
}

void InteractionObjectDrag::Show()
{
	Arrows.Allocate(7);
}
