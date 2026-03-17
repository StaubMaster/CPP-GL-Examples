#include "SceneInteraction/Data.hpp"



SceneInteractionData::SceneInteractionData(Physics2D::Manager & manager)
	: Manager(manager)
	, Selected(Undex::Invalid())
	, Hovering(Undex::Invalid())
	, Cursor()
	, TimeDelta(0.0f)
	, IsRunning(false)
	, IsSimulating(false)
{ }
