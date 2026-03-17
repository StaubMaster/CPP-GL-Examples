#ifndef  PHYSICS_2D_COLLISION_HPP
# define PHYSICS_2D_COLLISION_HPP

# include "Physics2D/Object.hpp"

# include "ValueType/AxisBox1D.hpp"

# include "ValueType/Point2D.hpp"
# include "ValueType/Ray2D.hpp"

namespace Physics2D
{
	struct PolyGonProjectionData
	{
		AxisBox1D		Box;
		unsigned int	MinUdx;
		unsigned int	MaxUdx;

		~PolyGonProjectionData();
		PolyGonProjectionData();

		PolyGonProjectionData(const PolyGonProjectionData & other);
		PolyGonProjectionData & operator=(const PolyGonProjectionData & other);

		void Consider(float val, unsigned int idx);

		static PolyGonProjectionData Project(
			const Object & obj,
			Point2D normal
		);
	};

	struct PolyGonContactData
	{
		bool			Valid;
		Point2D			Normal;
		Point2D			Contact;
		float			Distance;
		unsigned int	Contact0Udx;
		unsigned int	Contact1Udx;

		~PolyGonContactData();
		PolyGonContactData();
		PolyGonContactData(const PolyGonContactData & other);
		PolyGonContactData & operator=(const PolyGonContactData & other);

		bool Compare(const PolyGonContactData & other) const;

		static PolyGonContactData CheckContact(
			const Object & obj0,
			const Object & obj1,
			Point2D normal,
			float time
		);
		static PolyGonContactData CheckContact(
			const Object & obj0,
			const Object & obj1,
			float time
		);
	};

	void CollideLinear(
		Object & obj0,
		Object & obj1
	);
	void CollideRotate(
		Object & obj0,
		Object & obj1
	);
	void Collide(
		Object & obj0,
		Object & obj1
	);



/* (put this stuff somewhere else at some point)
	Constant (stays the same as long as the PolyGon dosent change)
		Mass
		Area ?
		Density ?
		Center of Mass
		Moment of Inertia
	Moving (changes as Velocity changes)
		Linear Velocity
		Linear Momentum
		Angular Velocity
		Angular Momentum
*/

	struct ObjectData
	{
		Point2D	CenterOfMass;
		float	MomentOfInertia;

		float	LinVel;
		float	LinMom;

		float	AngVel;
		float	AngMom;
	};
	ObjectData CalculateObjectData(Object & obj);

	struct ObjectContactForceData
	{
		Point2D		Contact;

		Point2D		Force;
		Point2D		ForcePos;
		Point2D		ForceRot;

		float	Torque;
	};
	ObjectContactForceData CalculateObjectContactForceData(Object & obj, Ray2D force);

	struct ObjectForceData
	{
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