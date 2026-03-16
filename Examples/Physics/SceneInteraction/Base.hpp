
//# include "SceneInteraction/Data.hpp"
# include "ValueType/Undex.hpp"
# include "Arrow2D/Object.hpp"

struct SceneInteractionBase
{
	::Undex	Undex;

	virtual ~SceneInteractionBase()
	{ }
	SceneInteractionBase()
		: Undex(Undex::Invalid())
		, Arrows()
	{ }

	virtual void Escape(SceneInteractionData & SceneData) = 0;

	virtual void Start(SceneInteractionData & SceneData) = 0;
	virtual void End(SceneInteractionData & SceneData)
	{
		(void)SceneData;
		if (Undex.IsValid())
		{
			Undex = Undex::Invalid();
			for (unsigned int i = 0; i < Arrows.Count(); i++)
			{
				Arrows[i] = Arrow2D::Inst::Data();
			}
		}
	}
	virtual void Update(SceneInteractionData & SceneData) = 0;

	Arrow2D::Object	Arrows;
	virtual void Show() = 0;
	void Hide();
};