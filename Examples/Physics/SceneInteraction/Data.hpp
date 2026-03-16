
# include "Physics2D/Manager.hpp"
# include "ValueType/Undex.hpp"
# include "ValueType/Point2D.hpp"

struct SceneInteractionData
{
	Physics2D::Manager &	Manager;
	Undex					Selected;
	Undex					Hovering;
	Point2D					Cursor;
	float					TimeDelta;
	bool					IsRunning;
	bool					IsSimulating;

	SceneInteractionData(Physics2D::Manager & manager)
		: Manager(manager)
		, Selected(Undex::Invalid())
		, Hovering(Undex::Invalid())
		, Cursor()
		, TimeDelta(0.0f)
		, IsRunning(false)
		, IsSimulating(false)
	{ }
};
