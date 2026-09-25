#ifndef  BOX_3_HPP
# define BOX_3_HPP

# include "ValueType/Box/__.hpp"

struct Bool3;

template<typename ValueType, typename VectorType, typename BoxType> struct Box_3 : public Box__<ValueType, VectorType, BoxType>
{
~Box_3() = default;
Box_3() = default;
Box_3(const Box_3 & other) = default;
Box_3 & operator=(const Box_3 & other) = default;

Box_3(VectorType min, VectorType max);



bool		IsNormal() const;
BoxType		Normalize() const;

void	Consider(const VectorType & vec);



Bool3	ContainsEdge(const VectorType & vec) const;
Bool3	ContainsInclusive(const VectorType & vec) const;
Bool3	ContainsExclusive(const VectorType & vec) const;

Bool3	IntersectsInclusive(const BoxType & box) const;
Bool3	IntersectsExclusive(const BoxType & box) const;



BoxType		operator+(const VectorType & vec) const;
BoxType		operator-(const VectorType & vec) const;
BoxType		operator*(const VectorType & vec) const;
BoxType		operator/(const VectorType & vec) const;
};

#endif