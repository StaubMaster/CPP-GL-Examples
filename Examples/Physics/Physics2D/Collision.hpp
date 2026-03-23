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

void Seperate(
	Object & obj0,
	Object & obj1,
	float timeDelta
);



struct ObjectForceData
{
	Point2D		Contact;	// the Relative Position of where the Force is applied
	Point2D		Force;		// Direction and Magniture of the Force

	Point2D		ForcePos;
	Point2D		ForceRot;
	float		Torque;

	~ObjectForceData();
	ObjectForceData();

	void	Calculate(Point2D contact, Point2D force);
	void	Calculate(Object & obj, Point2D contact, Point2D force);

	ObjectForceData(Point2D contact, Point2D force);
	ObjectForceData(Object & obj, Point2D contact, Point2D force);

	void	Apply(Object & obj);
};

Point2D DragObjectForce(
	Object & obj,
	Ray2D drag,
	float scalar
);

struct ObjectDragForceData
{
	Ray2D Drag;
	Line2D Contact;

	Ray2D Force;
	Ray2D ForcePos;
	Ray2D ForceRot;

	Ray2D ChangePos;
	Ray2D ChangeRot;
};
ObjectDragForceData ApplyDragForce(
	float timeDelta,
	Object & obj,
	Ray2D drag,
	float scalar,
	bool change
);
};

#endif