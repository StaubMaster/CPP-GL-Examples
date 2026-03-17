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
			{
				float values[2]
				{
					data.Torque.Dir.length2(),
					data.ChangeRot.Dir.length2(),
				};
				unsigned int ranks[2];
				::RankLengths(2, values, ranks);
				float sizes[2]
				{
					20.0f,
					16.0f,
				};
				//Arrows[ranks[0] + 4] = Arrow2D::Inst::Data(ColorF4(0.5f, 1.0f, 0.5f), sizes[ranks[0]], data.Torque);
				Arrows[ranks[1] + 4] = Arrow2D::Inst::Data(ColorF4(0.0f, 0.5f, 1.0f), sizes[ranks[1]], data.ChangeRot);
			}
			Arrows[6] = Arrow2D::Inst::Data(ColorF4(0.0f, 0.5f, 1.0f), 16.0f, data.ChangePos);
		}
	}
}

void InteractionObjectApplyForce::Show()
{
	Arrows.Allocate(7);
}
