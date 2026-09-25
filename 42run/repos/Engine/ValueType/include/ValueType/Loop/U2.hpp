#ifndef  LOOP_U_2_HPP
# define LOOP_U_2_HPP

# include "ValueType/Bool/2.hpp"
# include "ValueType/Vector/U2.hpp"
# include "ValueType/Box/U2.hpp"

struct LoopU2
{
	public:
	BoxU2	Range;
	Bool2	MinExclude;	// false means (udx >= Min); true means (udx > Min)
	Bool2	MaxExclude;	// false means (udx <= Max); true means (udx < Max)

	public:
	LoopU2();

	LoopU2(VectorU2 min, VectorU2 max);
	LoopU2(VectorU2 min, Bool2 minEx, VectorU2 max, Bool2 maxEx);

	~LoopU2();

	LoopU2(const LoopU2 & other);
	LoopU2 & operator=(const LoopU2 & other);

	public:
	VectorU2 Min() const;
	VectorU2 Max() const;

	public:
	Bool2 Check(VectorU2 udx) const;

	public:
	void Next(VectorU2 & udx) const;
	void Prev(VectorU2 & udx) const;
};

#endif