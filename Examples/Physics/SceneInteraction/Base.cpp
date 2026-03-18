#include "SceneInteraction/Base.hpp"



SceneInteractionBase::~SceneInteractionBase()
{ }
SceneInteractionBase::SceneInteractionBase()
	: Arrows()
{ }

void SceneInteractionBase::Hide()
{
	Arrows.Dispose();
}
