#ifndef  PHYSICS_2D_OBJECT_HPP
# define PHYSICS_2D_OBJECT_HPP

//# include "Physics2D/InstanceManager.hpp"

# include "ValueType/Trans2D.hpp"
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
	bool	RemoveNextFrame;
	
	IntrinsicData		IntData;
	ExtrinsicData		ExtData;

	bool	IsTangible;	// Interacts
	bool	IsStatic;	// Changes

	public:
	void	Update(float timeDelta);



	public:
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



	// PolyGon Stuff
	const ::PolyGon &	PolyGon() const;
	unsigned int		CornerCount() const;
	unsigned int		SideCount() const;

	bool				IsContaining(Point2D p) const;

	Point2D		RelativePositionOfIndex(unsigned int idx) const;
	Point2D		AbsolutePositionOfIndex(unsigned int idx) const;
	Point2D		AbsoluteVelocityOfIndex(unsigned int idx) const;

	/* Edge from [idx - 1] to [idx - 0]
		undefined if Corners.Count < 2
		undefiend if idx >= Corners.Count
	*/
	Line2D		EdgeOfIndex(unsigned int idx) const;



	// Graphics
	bool	DrawPolyGon;
	bool	DrawWireFrame;
	bool	DrawWireFrameBox;
	Arrow2D::Object	Arrows;

	public:
	void	GraphicsUpdate();

	void	Show_PolyGon();
	void	Show_WireFrame();
	void	Show_WireFrameBox();
	void	Show_Arrows();

	void	Hide_PolyGon();
	void	Hide_WireFrame();
	void	Hide_WireFrameBox();
	void	Hide_Arrows();



	~Object();
	Object();
	Object(const Object & other) ;
	Object & operator=(const Object & other);

	static Object & Construct(bool is_static);
	static Object & Construct(Trans2D now, bool is_static);
	static Object & Construct(Trans2D now, Trans2D vel, bool is_static);
};
};

#endif