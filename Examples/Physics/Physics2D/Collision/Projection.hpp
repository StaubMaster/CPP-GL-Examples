#ifndef  PHYSICS_2D_COLLISION_PROJECTION_HPP
# define PHYSICS_2D_COLLISION_PROJECTION_HPP

# include "Physics2D/Object.hpp"
# include "Miscellaneous/Container/Binary.hpp"

namespace Physics2D
{
namespace Collision
{
struct Projection
{
	static Object * DebugObject;
	static unsigned int DebugEdgeUndex;

	static bool DebugShow;
	static Point2D DebugOrigin;



	Point2D			Normal;
	Point2D			Position;
	float			Distance;

	~Projection();
	Projection();

	Projection(const Projection & other);
	Projection & operator=(const Projection & other);

	void Consider(const Projection & other);

	static Projection Project(
		Point2D origin,
		Point2D normal,
		Point2D point
	);

	static Projection Project(
		Point2D origin,
		Point2D normal,
		const Object & obj
	);
};
// make ContactData like this
struct ProjectionData
{
	Point2D		Normal;
	float		Limit;
	float		Sum;

	Container::Binary<Projection>	Projections;

	~ProjectionData();
	ProjectionData();

	ProjectionData(const ProjectionData & other);
	ProjectionData & operator=(const ProjectionData & other);

	void Consider(const Projection & projection);

	static ProjectionData Project(
		Point2D origin,
		Point2D normal,
		const Object & obj
	);
};
};
};

#endif