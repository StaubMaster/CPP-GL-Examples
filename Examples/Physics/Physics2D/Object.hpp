#ifndef  PHYSICS_2D_OBJECT_HPP
# define PHYSICS_2D_OBJECT_HPP

//# include "Physics2D/InstanceManager.hpp"

# include "Inst/Physics2D/Data.hpp"
//# include "Arrow2D/Inst/Data.hpp"
# include "Arrow2D/Object.hpp"

# include "Miscellaneous/EntryContainer/Entry.hpp"

# include "ValueType/Trans2D.hpp"

# include "ExtrinsicData.hpp"
# include "IntrinsicData.hpp"

class PolyGon;

namespace Physics2D
{
struct InstanceManager;

struct Object
{
	Physics2D::InstanceManager *	InstanceManager;
	Physics2D::Inst::Data			Data;
	Arrow2D::Object					Arrows;

	IntrinsicData		IntData;
	ExtrinsicData		ExtData;

	bool	RemoveNextFrame;

	bool	DrawPolyGon;
	bool	DrawWireFrame;
	bool	DrawWireFrameBox;

	bool	IsTangible;
	bool	IsStatic;

//	bool IsValid() const;
	const ::PolyGon *	PolyGon() const;

	public:
	void	Update();

	public:
	void	UpdateEntrys();

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

	/* RelativePositionOf
		Parameters:
			Absolute Position
		Return:
			Relative Position
	*/
	Point2D	RelativePositionOf(Point2D p) const;

	/* AbsolutePositionOf
		Parameters:
			Relative Position
		Return:
			Absolute Position
	*/
	Point2D	AbsolutePositionOf(Point2D p) const;

	/* AbsoluteVelocityOf
		Parameters:
			Relative Position
		Return:
			Absolute Velocity
	*/
	Point2D	AbsoluteVelocityOf(Point2D p) const;

	public:
	bool IsContaining(Point2D p) const;

	~Object();
	Object();
	Object(const Object & other) ;
	Object & operator=(const Object & other);

//	Object(Physics2D::InstanceManager & inst_manager, bool is_static);
//	Object(Physics2D::InstanceManager & inst_manager, Trans2D now, bool is_static);
//	Object(Physics2D::InstanceManager & inst_manager, Trans2D now, Trans2D vel, bool is_static);

	static Object & Construct(bool is_static);
	static Object & Construct(Trans2D now, bool is_static);
	static Object & Construct(Trans2D now, Trans2D vel, bool is_static);
};
};

#endif