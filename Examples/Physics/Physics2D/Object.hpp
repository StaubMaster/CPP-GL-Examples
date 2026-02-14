#ifndef  PHYSICS_2D_OBJECT_HPP
# define PHYSICS_2D_OBJECT_HPP

# include "Physics2D/MainInstance.hpp"

# include "Miscellaneous/EntryContainer/Entry.hpp"

# include "ValueType/Trans2D.hpp"

namespace Physics2D
{
struct Object
{
	Physics2D::MainInstance *		MainInstance;
	EntryContainer::Entry<Physics2D::Inst::Data>	Data;

	bool	IsStatic;
	float	Mass;

	bool				Valid() const;
	const ::PolyGon *	PolyGon() const;

	const Trans2D &		Now() const;
	const Trans2D &		Vel() const;

	Trans2D &			Now();
	Trans2D &			Vel();

	unsigned int	CornerCount() const;
	unsigned int	SideCount() const;
	Point2D			TransCorner(unsigned int idx) const;

	~Object();
	Object();
	Object(const Object & other);
	Object & operator=(const Object & other);

	Object(Physics2D::MainInstance & main_inst, bool is_static);
	Object(Physics2D::MainInstance & main_inst, Trans2D now, bool is_static);
	Object(Physics2D::MainInstance & main_inst, Trans2D now, Trans2D vel, bool is_static);
};
};

#endif