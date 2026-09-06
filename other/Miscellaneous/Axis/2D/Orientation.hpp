#ifndef  AXIS_2D_ORIENTATION_HPP
# define AXIS_2D_ORIENTATION_HPP

# include "Types.hpp"

struct VectorF2;
struct VectorU2;

namespace Axis2D
{
struct Orientation
{
	private:
	public:
	unsigned char Value = 0;
	public:

	Diag	GetDiag() const;
	Flip	GetFlip() const;

	void	SetDiag(Diag diag);
	void	SetFlip(Flip flip);

	~Orientation() = default;
	Orientation() = default;
	Orientation(const Orientation & other) = default;
	Orientation & operator=(const Orientation & other) = default;

	Orientation(Diag diag, Flip flip);

	Rel		absolute(const Rel & axis) const;
	Rel		relative(const Rel & axis) const;

	VectorU2	absolute(const VectorU2 & v) const;
	VectorF2	absolute(const VectorF2 & v) const;

	typedef VectorU2 (*SwizzlerU_Ptr)(const VectorU2 &);
	typedef VectorU2 (&SwizzlerU_Ref)(const VectorU2 &);
	SwizzlerU_Ref	absolute_U_Func() const;

	typedef VectorF2 (*SwizzlerF_Ptr)(const VectorF2 &);
	typedef VectorF2 (&SwizzlerF_Ref)(const VectorF2 &);
	SwizzlerF_Ref	absolute_F_Func() const;
};
};

#endif