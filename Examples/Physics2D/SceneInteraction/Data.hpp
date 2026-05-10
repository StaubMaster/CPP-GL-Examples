#ifndef  SCENE_INTERACTION_DATA_HPP
# define SCENE_INTERACTION_DATA_HPP

# include "Physics2D/Manager.hpp"
# include "ValueType/Undex.hpp"
# include "ValueType/VectorF2.hpp"
# include "Grid2D/Grid2D.hpp"
# include "FrameTime.hpp"

struct SceneInteractionData
{
	Physics2D::Manager &	Manager;
	Undex					Selected;
	Undex					Hovering;
	VectorF2					Cursor;
	Grid2D					Grid;
	::FrameTime				FrameTime;
	bool					IsRunning;
	bool					IsSimulating;

	SceneInteractionData(Physics2D::Manager & manager);
};

#endif