#ifndef  BOX_2_HPP
# define BOX_2_HPP

# include "ValueType/Box/__.hpp"

struct Bool2;

template<typename ValueType, typename VectorType, typename BoxType> struct Box_2 : public Box__<ValueType, VectorType, BoxType>
{
~Box_2() = default;
Box_2() = default;
Box_2(const Box_2 & other) = default;
Box_2 & operator=(const Box_2 & other) = default;

Box_2(VectorType min, VectorType max);



bool		IsNormal() const;
BoxType		Normalize() const;

void	Consider(const VectorType & vec);



Bool2	ContainsEdge(const VectorType & vec) const;
Bool2	ContainsInclusive(const VectorType & vec) const;
Bool2	ContainsExclusive(const VectorType & vec) const;

Bool2	IntersectsInclusive(const BoxType & box) const;
Bool2	IntersectsExclusive(const BoxType & box) const;
};

#endif