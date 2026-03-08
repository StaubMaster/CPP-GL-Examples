#ifndef  PHYSICS_2D_COLLISION_HPP
# define PHYSICS_2D_COLLISION_HPP

# include "Physics2D/Object.hpp"

# include "ValueType/AxisBox1D.hpp"
# include "ValueType/Point2D.hpp"
# include "ValueType/Point3D.hpp"

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

/* Arrows
	Center of Mass
	Contact
	Direction
*/
	struct ObjectForceData
	{
		Point2D Center;

		Point2D Contact;
		Point2D Direction;
		Point2D Normal;

		Point2D Perp;

		Point2D Impulse;
	};
	ObjectForceData ApplyImpulse(Object & obj, Point2D pos, Point2D dir, float force, bool change);
};

#endif