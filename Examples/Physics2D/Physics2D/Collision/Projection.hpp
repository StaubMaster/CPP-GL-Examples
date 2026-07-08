#ifndef  PHYSICS_2D_COLLISION_PROJECTION_HPP
# define PHYSICS_2D_COLLISION_PROJECTION_HPP

# include "Physics2D/Object.hpp"
# include "Generics/Container/Binary.hpp"

namespace Physics2D
{
namespace Collision
{
struct Projection
{
	static Object * DebugObject;
	static unsigned int DebugEdgeUndex;

	static bool DebugShow;
	static VectorF2 DebugOrigin;



	VectorF2			Position;
	float			Distance;

	~Projection();
	Projection();

	Projection(const Projection & other);
	Projection & operator=(const Projection & other);

	static Projection Project(
		VectorF2 origin,
		VectorF2 normal,
		VectorF2 point
	);
};
};
};

#endif