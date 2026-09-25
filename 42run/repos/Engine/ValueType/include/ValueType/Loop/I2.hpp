#ifndef  LOOP_I_2_HPP
# define LOOP_I_2_HPP

# include "ValueType/Bool/2.hpp"
# include "ValueType/Vector/I2.hpp"
# include "ValueType/Box/I2.hpp"

struct LoopI2
{
	public:
	BoxI2	Range;
	Bool2	MinExclude;	// false means (idx >= Min); true means (idx > Min)
	Bool2	MaxExclude;	// false means (idx <= Max); true means (idx < Max)

	public:
	~LoopI2();
	LoopI2();

	LoopI2(VectorI2 size);

	LoopI2(VectorI2 min, VectorI2 max);
	LoopI2(VectorI2 min, Bool2 minEx, VectorI2 max, Bool2 maxEx);

	LoopI2(BoxI2 box);
	LoopI2(BoxI2 box, Bool2 minEx, Bool2 maxEx);

	LoopI2(const LoopI2 & other);
	LoopI2 & operator=(const LoopI2 & other);

	public:
	VectorI2	Min() const;
	VectorI2	Max() const;
	VectorI2	Size() const;

	public:
	Bool2		Check(VectorI2 idx) const;

	public:
	void	Next(VectorI2 & idx) const;
	void	Prev(VectorI2 & idx) const;
};

#endif