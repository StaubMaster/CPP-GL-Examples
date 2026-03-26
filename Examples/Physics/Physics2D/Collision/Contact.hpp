#ifndef  PHYSICS_2D_COLLISION_CONTACT_HPP
# define PHYSICS_2D_COLLISION_CONTACT_HPP

# include "Physics2D/Object.hpp"

# include "Physics2D/Collision/Projection.hpp"

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
	bool		Valid;

	Point2D		Normal;
	float		Limit;
	float		Sum;

	Container::Binary<Projection>	Projections;

	~ContactData();
	ContactData();

	ContactData(const ContactData & other);
	ContactData & operator=(const ContactData & other);

	void Consider(const Projection & projection);

	static ContactData Project(
		Point2D origin,
		Point2D normal,
		const Object & obj
	);

	bool Compare(const ContactData & other) const;
	void Consider(const ContactData & other);

	static bool Contact(
		ContactData & data,
		const Object & edges,
		const Object & contacts,
		float timeDelta
	);

	static ContactData Contact(
		const Object & obj0,
		const Object & obj1,
		float timeDelta
	);
};
};

};

#endif