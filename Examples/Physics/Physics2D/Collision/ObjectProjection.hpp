#ifndef  PHYSICS_2D_COLLISION_OBJECT_PROJECTION_HPP
# define PHYSICS_2D_COLLISION_OBJECT_PROJECTION_HPP

# include "Physics2D/Object.hpp"

# include "ValueType/AxisBox1D.hpp"

namespace Physics2D
{
namespace Collision
{
struct ObjectProjection
{
	static Object * DebugObject;
	static unsigned int DebugEdgeUndex;

	static bool DebugShow;
	static Point2D DebugOrigin;

	float			Distance;
	unsigned int	Undex;

	~ObjectProjection();
	ObjectProjection();

	ObjectProjection(const ObjectProjection & other);
	ObjectProjection & operator=(const ObjectProjection & other);

	void Consider(float val, unsigned int idx);

	static ObjectProjection Project(
		Point2D origin,
		Point2D normal,
		const Object & obj
	);
};
};
};

#endif