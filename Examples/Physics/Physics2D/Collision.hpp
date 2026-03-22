#ifndef  PHYSICS_2D_COLLISION_HPP
# define PHYSICS_2D_COLLISION_HPP

# include "Physics2D/Object.hpp"

# include "ValueType/AxisBox1D.hpp"

# include "ValueType/Point2D.hpp"
# include "ValueType/Ray2D.hpp"

# include "ValueType/Matrix3x3.hpp"

namespace Physics2D
{
namespace Collision
{
struct ContactData
{
	bool			Valid;
	unsigned int	Undex0;
	unsigned int	Undex1;

	Point2D			Normal;
	Point2D			Position;
	float			Distance;

	~ContactData();
	ContactData();
	ContactData(const ContactData & other);
	ContactData & operator=(const ContactData & other);

	bool Compare(const ContactData & other) const;
	void Consider(const ContactData & other);

	static Point2D CalculateNormal(const Object & obj, unsigned int idx);

	static ContactData CheckContact(
		const Object & obj0,
		const Object & obj1,
		Point2D normal,
		float timeDelta
	);
	static ContactData CheckContact(
		const Object & obj0,
		const Object & obj1,
		float timeDelta
	);

	struct ResolveData
	{
		Point2D	Pos0;
		Point2D	Pos1;
		Angle2D	Rot0;
		Angle2D	Rot1;
	};
	ResolveData Resolve(
		Object & obj0,
		Object & obj1,
		float timeDelta
	);
};
};

void Collide(
	Object & obj0,
	Object & obj1,
	float timeDelta
);

struct ObjectDragData
{
	Point2D		Contact;

	Point2D		Force;
	Point2D		ForcePos;
	Point2D		ForceRot;

	float	Torque;
};
ObjectDragData CalculateObjectDragData(Object & obj, Ray2D drag, float scalar);

struct ObjectForceData
{
	Ray2D Drag;
	Line2D Contact;

	Ray2D Force;
	Ray2D ForcePos;
	Ray2D ForceRot;

	Ray2D ChangePos;
	Ray2D ChangeRot;
};
ObjectForceData ApplyForce(float timeDelta, Object & obj, Ray2D drag, float scalar, bool change);
};

#endif