#ifndef  PHYSICS_2D_OBJECT_HPP
# define PHYSICS_2D_OBJECT_HPP

//# include "Physics2D/InstanceManager.hpp"

# include "ValueType/Trans/2D.hpp"
# include "Arrow2D/Object.hpp"

# include "PolyGon/Object.hpp"

# include "Miscellaneous/EntryContainer/Entry.hpp"

# include "ValueType/Trans/2D.hpp"

# include "ExtrinsicData.hpp"
# include "IntrinsicData.hpp"

class PolyGon;

namespace Physics2D
{
struct InstanceManager;

struct Object
{
	Physics2D::InstanceManager *	InstanceManager;
	::PolyGonObject					PolyGonObject;
	::PolyGonObject					BoundObject;
	bool	RemoveNextFrame;

	IntrinsicData		IntData;
	ExtrinsicData		ExtData;

	bool	IsTangible;		// Interacts
	bool	IsStatic;		// Changes

	public:
	void	Update(float timeDelta);



	public:
	/* RelativePositionOf
		Parameters:
			Absolute Position
		Return:
			Relative Position
	*/
	VectorF2	RelativePositionOf(VectorF2 p) const;

	/* AbsolutePositionOf
		Parameters:
			Relative Position
		Return:
			Absolute Position
	*/
	VectorF2	AbsolutePositionOf(VectorF2 p) const;

	/* AbsoluteVelocityOf
		Parameters:
			Relative Position
		Return:
			Absolute Velocity
	*/
	VectorF2	AbsoluteVelocityOf(VectorF2 p) const;



	// PolyGon Stuff
	const ::PolyGon &	PolyGon() const;
	unsigned int		CornerCount() const;
	unsigned int		SideCount() const;

	bool				IsContaining(VectorF2 p) const;

	VectorF2		RelativePositionOfIndex(unsigned int idx) const;
	VectorF2		AbsolutePositionOfIndex(unsigned int idx) const;
	VectorF2		AbsoluteVelocityOfIndex(unsigned int idx) const;

	/* Edge from [idx - 1] to [idx - 0]
		undefined if Corners.Count < 2
		undefiend if idx >= Corners.Count
	*/
	LineF2		EdgeOfIndex(unsigned int idx) const;



	// Graphics
//	bool	DrawPolyGon;
//	bool	DrawWireFrame;
//	bool	DrawWireFrameBox;
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