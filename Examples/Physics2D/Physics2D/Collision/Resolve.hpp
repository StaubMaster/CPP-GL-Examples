#ifndef  PHYSICS_2D_COLLISION_RESOLVE_HPP
# define PHYSICS_2D_COLLISION_RESOLVE_HPP

# include "Physics2D/Object.hpp"

# include "ValueType/Box/F1.hpp"

# include "ValueType/VectorF2.hpp"
# include "ValueType/Ray2D.hpp"

# include "ValueType/Matrix3x3.hpp"

# include "Physics2D/Collision/Projection.hpp"
# include "Physics2D/Collision/Contact.hpp"

namespace Physics2D
{
namespace Collision
{

struct ResolveData
{
	VectorF2	Pos0;
	VectorF2	Pos1;
	Angle	Rot0;
	Angle	Rot1;
};

ResolveData Resolve(
	VectorF2 normal,
	Projection & projection,
	Object & obj0,
	Object & obj1,
	float timeDelta
);

ResolveData Resolve(
	ContactData & contact,
	Object & obj0,
	Object & obj1,
	float timeDelta
);

};
};

#endif