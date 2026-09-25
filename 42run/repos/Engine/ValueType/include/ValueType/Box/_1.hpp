#ifndef  BOX_1_HPP
# define BOX_1_HPP

# include "ValueType/Box/__.hpp"



template<typename ValueType, typename VectorType, typename BoxType> struct Box_1 : public Box__<ValueType, VectorType, BoxType>
{
~Box_1() = default;
Box_1() = default;
Box_1(const Box_1 & other) = default;
Box_1 & operator=(const Box_1 & other) = default;

Box_1(VectorType min, VectorType max);


void	Consider(const VectorType & vec);

bool		IsNormal() const;
BoxType		Normalize() const;



bool	ContainsEdge(const VectorType & vec) const;
bool	ContainsInclusive(const VectorType & vec) const;
bool	ContainsExclusive(const VectorType & vec) const;

bool	IntersectsInclusive(const BoxType & box) const;
bool	IntersectsExclusive(const BoxType & box) const;
};

#endif