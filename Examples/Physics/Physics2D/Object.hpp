#ifndef  PHYSICS_2D_OBJECT_HPP
# define PHYSICS_2D_OBJECT_HPP

# include "Physics2D/InstanceManager.hpp"

# include "Miscellaneous/EntryContainer/Entry.hpp"

# include "ValueType/Trans2D.hpp"

namespace Physics2D
{
struct Object
{
	Physics2D::InstanceManager *		InstanceManager;

	Physics2D::Inst::Data			Data;

	EntryContainer::Entry<Physics2D::Inst::Data>	Data_PolyGon;
	EntryContainer::Entry<Physics2D::Inst::Data>	Data_WireFrame;
	EntryContainer::Entry<Physics2D::Inst::Data>	Data_WireFrameBox;
	EntryContainer::Entry<Arrow2D::Inst::Data>		Data_Arrows;

	bool	IsStatic;
	float	Mass;

	bool				Valid() const;
	const ::PolyGon *	PolyGon() const;
	void				Update();

	const Trans2D &		Now() const;
	const Trans2D &		Vel() const;

	Trans2D &			Now();
	Trans2D &			Vel();

	void	Show_PolyGon();
	void	Show_WireFrame();
	void	Show_WireFrameBox();
	void	Show_Arrows();

	void	Hide_PolyGon();
	void	Hide_WireFrame();
	void	Hide_WireFrameBox();
	void	Hide_Arrows();

	unsigned int	CornerCount() const;
	unsigned int	SideCount() const;

	Point2D	CornerFromIndex(unsigned int idx) const;

	Point2D	RelativePositionOf(Point2D p) const;
	Point2D	AbsolutePositionOf(Point2D p) const;
	Point2D	AbsoluteVelocityOf(Point2D p) const;

	~Object();
	Object();
	Object(const Object & other);
	Object & operator=(const Object & other);

	Object(Physics2D::InstanceManager & inst_manager, bool is_static);
	Object(Physics2D::InstanceManager & inst_manager, Trans2D now, bool is_static);
	Object(Physics2D::InstanceManager & inst_manager, Trans2D now, Trans2D vel, bool is_static);

	public:
	bool IsContaining(Point2D p) const;

	public:
	void UpdateArrows();
};
};

#endif