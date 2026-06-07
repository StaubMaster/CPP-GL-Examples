#ifndef  AXIS_ORIENTATION_HPP
# define AXIS_ORIENTATION_HPP

# include "Enums.hpp"

# include "ValueType/Vector/F3.hpp"
# include "ValueType/Vector/U3.hpp"

struct AxisOrientation
{
	private:
	unsigned char Value;
	public:

	Diag	GetDiag() const;
	Flip	GetFlip() const;

	void	SetDiag(Diag diag);
	void	SetFlip(Flip flip);

	~AxisOrientation();
	AxisOrientation();

	AxisOrientation(const AxisOrientation & other);
	AxisOrientation & operator=(const AxisOrientation & other);

	void	make(Diag diag, Flip flip);
	void	make(AxisRel origin, AxisRel target);
	void	make(AxisRel origin0, AxisRel target0, AxisRel origin1, AxisRel target1); // make this a static function ?

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

	typedef VectorU3 (*SwizzlerU_Ptr)(const VectorU3 &);
	typedef VectorU3 (&SwizzlerU_Ref)(const VectorU3 &);

	SwizzlerU_Ref	absoluteU_Func() const;

	VectorU3	absolute(VectorU3 v) const;
	VectorF3	absolute(VectorF3 v) const;

	AxisRel		absolute(AxisRel axis) const;
	AxisRel		relative(AxisRel axis) const;
};

#endif