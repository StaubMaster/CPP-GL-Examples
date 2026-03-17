#include "SceneInteraction/Force.hpp"
#include "Arrow2D/RankLengths.hpp"



InteractionObjectApplyForce::InteractionObjectApplyForce()
	: SceneInteractionBase()
{ }

void InteractionObjectApplyForce::Escape(SceneInteractionData & SceneData)
{
	(void)SceneData;
}

void InteractionObjectApplyForce::Start(SceneInteractionData & SceneData)
{
	Undex = SceneData.Hovering;
	if (Undex.IsValid())
	{
		Contact = SceneData.Manager.Objects[Undex.Value] -> RelativePositionOf(SceneData.Cursor);
	}
}
void InteractionObjectApplyForce::Update(SceneInteractionData & SceneData)
{
	if (Undex.IsValid())
	{
		Ray2D drag;
		drag.Pos = SceneData.Manager.Objects[Undex.Value] -> AbsolutePositionOf(Contact);
		drag.Dir = SceneData.Cursor - drag.Pos;

		Physics2D::ObjectForceData data = Physics2D::ApplyForce(SceneData.TimeDelta, *(SceneData.Manager.Objects[Undex.Value]), drag, 10.0f, SceneData.IsSimulating);

		if (Arrows.Is())
		{
			Arrows[0] = Arrow2D::Inst::Data(ColorF4(0.0f, 0.0f, 0.0f), 16.0f, data.Contact);

			Arrows[1] = Arrow2D::Inst::Data(ColorF4(1.0f, 0.5f, 0.0f), 24.0f, data.Force);
			Arrows[2] = Arrow2D::Inst::Data(ColorF4(1.0f, 0.5f, 0.0f), 16.0f, data.ForcePos);
			Arrows[3] = Arrow2D::Inst::Data(ColorF4(1.0f, 0.5f, 0.0f), 16.0f, data.ForceRot);

			Arrows[4] = Arrow2D::Inst::Data(ColorF4(0.0f, 0.5f, 1.0f), 16.0f, data.ChangeRot);
			Arrows[5] = Arrow2D::Inst::Data(ColorF4(0.0f, 0.5f, 1.0f), 16.0f, data.ChangePos);
		}
	}
}

void InteractionObjectApplyForce::Show()
{
	Arrows.Allocate(6);
}
