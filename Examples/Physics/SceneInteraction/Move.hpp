
//# include "SceneInteraction/Base.hpp"
# include "ValueType/Point2D.hpp"

struct InteractionObjectMove : public SceneInteractionBase
{
	Point2D	Origin;
	Point2D	Offset;

	InteractionObjectMove()
		: SceneInteractionBase()
	{ }

	void Escape(SceneInteractionData & SceneData) override
	{
		if (Undex.IsValid())
		{
			Trans2D & now = SceneData.Manager.Objects[Undex.Value] -> Data.Now;
			now.Pos = Origin;
			End(SceneData);
		}
	}

	void Start(SceneInteractionData & SceneData) override
	{
		Undex = SceneData.Hovering;
		if (Undex.IsValid())
		{
			Trans2D & now = SceneData.Manager.Objects[Undex.Value] -> Data.Now;
			Origin = now.Pos;
			Offset = SceneData.Cursor - now.Pos;
		}
	}
	void Update(SceneInteractionData & SceneData) override
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

	void Show() override
	{
		Arrows.Allocate(2);
	}
};