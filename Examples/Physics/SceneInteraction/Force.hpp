
//# include "SceneInteraction/Base.hpp"
# include "ValueType/Angle2D.hpp"

# include "Physics2D/Collision.hpp"



// put this in Arrow somewhere
static void RankLengths(unsigned int count, float values[], unsigned int ranks[])
{
	for (unsigned int j = 0; j < count; j++)
	{
		ranks[j] = 0;
		for (unsigned int i = 0; i < count; i++)
		{
			if (i != j)
			{
				if (values[j] < values[i])
				{
					ranks[j]++;
				}
			}
		}
	}
}

struct InteractionObjectApplyForce : public SceneInteractionBase
{
	Point2D	Contact;

	InteractionObjectApplyForce()
		: SceneInteractionBase()
	{ }

	void Escape(SceneInteractionData & SceneData) override
	{
		(void)SceneData;
	}

	void Start(SceneInteractionData & SceneData) override
	{
		Undex = SceneData.Hovering;
		if (Undex.IsValid())
		{
			Contact = SceneData.Manager.Objects[Undex.Value] -> RelativePositionOf(SceneData.Cursor);
		}
	}
	void Update(SceneInteractionData & SceneData) override
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

				Arrows[1] = Arrow2D::Inst::Data(ColorF4(1.0f, 0.5f, 0.5f), 24.0f, data.Force);
				Arrows[2] = Arrow2D::Inst::Data(ColorF4(1.0f, 0.5f, 0.5f), 16.0f, data.ForcePos);
				Arrows[3] = Arrow2D::Inst::Data(ColorF4(1.0f, 0.5f, 0.5f), 16.0f, data.ForceRot);
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
					Arrows[ranks[0] + 4] = Arrow2D::Inst::Data(ColorF4(0.5f, 0.5f, 1.0f), sizes[ranks[0]], data.Torque);
					Arrows[ranks[1] + 4] = Arrow2D::Inst::Data(ColorF4(0.5f, 1.0f, 0.5f), sizes[ranks[1]], data.ChangeRot);
				}
				Arrows[6] = Arrow2D::Inst::Data(ColorF4(0.5f, 1.0f, 0.5f), 16.0f, data.ChangePos);
			}
		}
	}

	void Show() override
	{
		Arrows.Allocate(7);
	}
};