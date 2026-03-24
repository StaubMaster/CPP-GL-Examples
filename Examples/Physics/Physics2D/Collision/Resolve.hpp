#ifndef  PHYSICS_2D_COLLISION_RESOLVE_HPP
# define PHYSICS_2D_COLLISION_RESOLVE_HPP

# include "Physics2D/Object.hpp"

# include "ValueType/AxisBox1D.hpp"

# include "ValueType/Point2D.hpp"
# include "ValueType/Ray2D.hpp"

# include "ValueType/Matrix3x3.hpp"

# include "Physics2D/Collision/Contact.hpp"

namespace Physics2D
{
namespace Collision
{

struct ResolveData
{
	Point2D	Pos0;
	Point2D	Pos1;
	Angle2D	Rot0;
	Angle2D	Rot1;
};

ResolveData Resolve(
	ContactData & contact,
	Object & obj0,
	Object & obj1,
	float timeDelta
);

};
};

#endif