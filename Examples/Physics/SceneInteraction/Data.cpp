#include "SceneInteraction/Data.hpp"



SceneInteractionData::SceneInteractionData(Physics2D::Manager & manager)
	: Manager(manager)
	, Selected(Undex::Invalid())
	, Hovering(Undex::Invalid())
	, Cursor()
	, Grid(0.1f, 15.0f)
	, FrameTime(60.0f)
	, IsRunning(false)
	, IsSimulating(false)
{ }
