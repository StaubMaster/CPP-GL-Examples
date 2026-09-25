#ifndef  DISPLAY_NORMAL_POSITION_HPP
# define DISPLAY_NORMAL_POSITION_HPP

# include "ValueType/Vector/F2.hpp"

struct NormalPosition
{
	VectorF2	Rel;
	VectorF2	Abs;

	~NormalPosition();
	NormalPosition();

	NormalPosition(const NormalPosition & other);
	NormalPosition & operator=(const NormalPosition & other);

	static VectorF2		RelToAbs(VectorF2 pos);
	static VectorF2		AbsToRel(VectorF2 pos);

	static NormalPosition	FromRel(VectorF2 pos);
	static NormalPosition	FromAbs(VectorF2 pos);
};


#endif