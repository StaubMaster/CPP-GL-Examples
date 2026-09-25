#include "ValueType/Box/_1.hpp"

/*
template<typename ValueType, typename VectorType, typename BoxType>
Box_1<ValueType, VectorType, BoxType>::
*/



template<typename ValueType, typename VectorType, typename BoxType>Box_1<ValueType, VectorType, BoxType>::Box_1(VectorType min, VectorType max)
	: Box__<ValueType, VectorType, BoxType>(min, max)
{ }



template<typename ValueType, typename VectorType, typename BoxType> void	Box_1<ValueType, VectorType, BoxType>::Consider(const VectorType & vec)
{
	if (vec < (this -> Min)) { (this -> Min) = vec; }

	if (vec > (this -> Max)) { (this -> Max) = vec; }
}

template<typename ValueType, typename VectorType, typename BoxType> bool		Box_1<ValueType, VectorType, BoxType>::IsNormal() const
{
	return ((this -> Min) <= (this -> Max));
}
/*template<typename ValueType, typename VectorType, typename BoxType> BoxType		Box_1<ValueType, VectorType, BoxType>::Normalize() const
{
	return BoxType(
		Min.Min(Max),
		Max.Max(Min)
	);
}*/





template<typename ValueType, typename VectorType, typename BoxType> bool Box_1<ValueType, VectorType, BoxType>::ContainsEdge(const VectorType & vec) const			{ return (vec == this -> Min) | (vec == this -> Max); }
template<typename ValueType, typename VectorType, typename BoxType> bool Box_1<ValueType, VectorType, BoxType>::ContainsInclusive(const VectorType & vec) const		{ return (vec >= this -> Min) & (vec <= this -> Max); }
template<typename ValueType, typename VectorType, typename BoxType> bool Box_1<ValueType, VectorType, BoxType>::ContainsExclusive(const VectorType & vec) const		{ return (vec >  this -> Min) & (vec <  this -> Max); }

template<typename ValueType, typename VectorType, typename BoxType> bool Box_1<ValueType, VectorType, BoxType>::IntersectsInclusive(const BoxType & box) const		{ return (this -> Max >= box.Min) & (this -> Min <= box.Max); }
template<typename ValueType, typename VectorType, typename BoxType> bool Box_1<ValueType, VectorType, BoxType>::IntersectsExclusive(const BoxType & box) const		{ return (this -> Max >  box.Min) & (this -> Min <  box.Max); }
