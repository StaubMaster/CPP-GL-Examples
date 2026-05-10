#ifndef  PHYSICS_2D_COLLISION_HPP
# define PHYSICS_2D_COLLISION_HPP

# include "Physics2D/Object.hpp"

# include "ValueType/Box/F1.hpp"

# include "ValueType/VectorF2.hpp"
# include "ValueType/Ray2D.hpp"

# include "ValueType/Matrix3x3.hpp"



namespace Physics2D
{

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
	VectorF2		Contact;	// the Relative Position of where the Force is applied
	VectorF2		Force;		// Direction and Magniture of the Force

	VectorF2		ForcePos;
	VectorF2		ForceRot;
	float		Torque;

	~ObjectForceData();
	ObjectForceData();

	void	Calculate(VectorF2 contact, VectorF2 force);
	void	Calculate(Object & obj, VectorF2 contact, VectorF2 force);

	ObjectForceData(VectorF2 contact, VectorF2 force);
	ObjectForceData(Object & obj, VectorF2 contact, VectorF2 force);

	void	Apply(Object & obj);
};

VectorF2 DragObjectForce(
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