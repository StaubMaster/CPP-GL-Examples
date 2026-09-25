#include "ValueType/Box/_3.hpp"
#include "ValueType/Bool/3.hpp"

/*
template<typename ValueType, typename VectorType, typename BoxType>
Box_3<ValueType, VectorType, BoxType>::
*/



template<typename ValueType, typename VectorType, typename BoxType>Box_3<ValueType, VectorType, BoxType>::Box_3(VectorType min, VectorType max)
	: Box__<ValueType, VectorType, BoxType>(min, max)
{ }



template<typename ValueType, typename VectorType, typename BoxType> void	Box_3<ValueType, VectorType, BoxType>::Consider(const VectorType & vec)
{
	if (vec.X < (this -> Min.X)) { (this -> Min.X) = vec.X; }
	if (vec.Y < (this -> Min.Y)) { (this -> Min.Y) = vec.Y; }
	if (vec.Z < (this -> Min.Z)) { (this -> Min.Z) = vec.Z; }

	if (vec.X > (this -> Max.X)) { (this -> Max.X) = vec.X; }
	if (vec.Y > (this -> Max.Y)) { (this -> Max.Y) = vec.Y; }
	if (vec.Z > (this -> Max.Z)) { (this -> Max.Z) = vec.Z; }
}

template<typename ValueType, typename VectorType, typename BoxType> bool		Box_3<ValueType, VectorType, BoxType>::IsNormal() const
{
	return ((this -> Min) <= (this -> Max)).All(true);
}
template<typename ValueType, typename VectorType, typename BoxType> BoxType		Box_3<ValueType, VectorType, BoxType>::Normalize() const
{
	return BoxType(
		(this -> Min).Min(this -> Max),
		(this -> Max).Max(this -> Min)
	);
}





template<typename ValueType, typename VectorType, typename BoxType> Bool3 Box_3<ValueType, VectorType, BoxType>::ContainsEdge(const VectorType & vec) const			{ return (vec == this -> Min) | (vec == this -> Max); }
template<typename ValueType, typename VectorType, typename BoxType> Bool3 Box_3<ValueType, VectorType, BoxType>::ContainsInclusive(const VectorType & vec) const	{ return (vec >= this -> Min) & (vec <= this -> Max); }
template<typename ValueType, typename VectorType, typename BoxType> Bool3 Box_3<ValueType, VectorType, BoxType>::ContainsExclusive(const VectorType & vec) const	{ return (vec >  this -> Min) & (vec <  this -> Max); }

template<typename ValueType, typename VectorType, typename BoxType> Bool3 Box_3<ValueType, VectorType, BoxType>::IntersectsInclusive(const BoxType & box) const		{ return (this -> Max >= box.Min) & (this -> Min <= box.Max); }
template<typename ValueType, typename VectorType, typename BoxType> Bool3 Box_3<ValueType, VectorType, BoxType>::IntersectsExclusive(const BoxType & box) const		{ return (this -> Max >  box.Min) & (this -> Min <  box.Max); }



template<typename ValueType, typename VectorType, typename BoxType> BoxType		Box_3<ValueType, VectorType, BoxType>::operator+(const VectorType & vec) const { return BoxType(this -> Min + vec, this -> Max + vec); }
template<typename ValueType, typename VectorType, typename BoxType> BoxType		Box_3<ValueType, VectorType, BoxType>::operator-(const VectorType & vec) const { return BoxType(this -> Min - vec, this -> Max - vec); }
template<typename ValueType, typename VectorType, typename BoxType> BoxType		Box_3<ValueType, VectorType, BoxType>::operator*(const VectorType & vec) const { return BoxType(this -> Min * vec, this -> Max * vec); }
template<typename ValueType, typename VectorType, typename BoxType> BoxType		Box_3<ValueType, VectorType, BoxType>::operator/(const VectorType & vec) const { return BoxType(this -> Min / vec, this -> Max / vec); }
