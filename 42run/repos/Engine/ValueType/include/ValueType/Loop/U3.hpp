#ifndef  LOOP_U_3_HPP
# define LOOP_U_3_HPP

# include "ValueType/Bool/3.hpp"
# include "ValueType/Vector/U3.hpp"
# include "ValueType/Box/U3.hpp"

struct LoopU3
{
	public:
	BoxU3	Range;
	Bool3	MinExclude;	// false means (udx >= Min); true means (udx > Min)
	Bool3	MaxExclude;	// false means (udx <= Max); true means (udx < Max)

	public:
	~LoopU3();
	LoopU3();

	LoopU3(VectorU3 size);

	LoopU3(VectorU3 min, VectorU3 max);
	LoopU3(VectorU3 min, Bool3 minEx, VectorU3 max, Bool3 maxEx);

	LoopU3(BoxU3 box);
	LoopU3(BoxU3 box, Bool3 minEx, Bool3 maxEx);

	LoopU3(const LoopU3 & other);
	LoopU3 & operator=(const LoopU3 & other);

	public:
	VectorU3	Min() const;
	VectorU3	Max() const;
	VectorU3	Size() const;

	public:
	Bool3	Check(VectorU3 udx) const;

	public:
	void	Next(VectorU3 & udx) const;
	void	Prev(VectorU3 & udx) const;
};

#endif