#include "SceneInteraction/Base.hpp"



SceneInteractionBase::~SceneInteractionBase()
{ }
SceneInteractionBase::SceneInteractionBase()
	: Undex(Undex::Invalid())
	, Arrows()
{ }

void SceneInteractionBase::End(SceneInteractionData & SceneData)
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

void SceneInteractionBase::Hide()
{
	Arrows.Dispose();
}
