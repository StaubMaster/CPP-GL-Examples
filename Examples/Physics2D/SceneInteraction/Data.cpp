#include "SceneInteraction/Data.hpp"



SceneInteractionData::SceneInteractionData(Physics2D::Manager & manager)
	: Manager(manager)
	, Selected(Undex::Invalid())
	, Hovering(Undex::Invalid())
	, Cursor()
	, Grid(10, 24)
	, FrameTime(60.0f)
	, IsRunning(false)
	, IsSimulating(false)
{ }
