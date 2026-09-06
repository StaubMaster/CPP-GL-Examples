#ifndef  AXIS_3D_ORIENTATION_HPP
# define AXIS_3D_ORIENTATION_HPP

# include "Types.hpp"

struct VectorF3;
struct VectorU3;

namespace Axis3D
{
struct Orientation
{
	private:
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

	void	make(Rel origin, Rel target);
	void	make(Rel origin0, Rel target0, Rel origin1, Rel target1); // make this a static function ?

	/*
		currently
			VectorU3 and VectorF3 are in range [0;1] and rotate around 0.5f
		should VectorF3 be [-1;+1] and rotate around 0.0f ?
	*/

	// these functions are made of 2 switch statements
	// thats fast enough for single use, but doing it multiple times gets slow ?
	// there are only 24 combinations, make hardcoded functions that "swizzle" the coordinates
	// then just make a function that returns a function pointer
	// or function referance

	Rel		absolute(const Rel & axis) const;
	Rel		relative(const Rel & axis) const;

	VectorU3	absolute(const VectorU3 & v) const;
	VectorF3	absolute(const VectorF3 & v) const;

	typedef VectorU3 (*SwizzlerU_Ptr)(const VectorU3 &);
	typedef VectorU3 (&SwizzlerU_Ref)(const VectorU3 &);
	SwizzlerU_Ref	absolute_U_Func() const;

	typedef VectorF3 (*SwizzlerF_Ptr)(const VectorF3 &);
	typedef VectorF3 (&SwizzlerF_Ref)(const VectorF3 &);
	SwizzlerF_Ref	absolute_F_Func() const;
};
};

#endif