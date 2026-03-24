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
	AxisBox1D		Box;
	unsigned int	MinUdx;
	unsigned int	MaxUdx;

	~ObjectProjection();
	ObjectProjection();

	ObjectProjection(const ObjectProjection & other);
	ObjectProjection & operator=(const ObjectProjection & other);

	void Consider(float val, unsigned int idx);

	static ObjectProjection Project(Point2D normal, const Object & obj);
};
struct ObjectProjectionOverlap
{
	bool	Valid;
	float	Distance;
	unsigned	Undex0;
	unsigned	Undex1;

	~ObjectProjectionOverlap();
	ObjectProjectionOverlap();

	ObjectProjectionOverlap(const ObjectProjectionOverlap & other);
	ObjectProjectionOverlap & operator=(const ObjectProjectionOverlap & other);

	static ObjectProjectionOverlap Overlap(ObjectProjection proj0, ObjectProjection proj1);
	static ObjectProjectionOverlap Overlap(Point2D normal, const Object & obj0, const Object & ob1);
};
};
};

#endif