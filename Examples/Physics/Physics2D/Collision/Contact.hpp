#ifndef  PHYSICS_2D_COLLISION_CONTACT_HPP
# define PHYSICS_2D_COLLISION_CONTACT_HPP

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
		Point2D origin,
		Point2D normal,
		const Object & obj,
		float timeDelta
	);

	static ContactData CheckContact(
		const Object & obj0,
		const Object & obj1,
		float timeDelta
	);
};
};

};

#endif