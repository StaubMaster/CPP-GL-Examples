#include "ValueType/Box/__.hpp"

/*
template<typename ValueType, typename VectorType, typename BoxType>
Box__<ValueType, VectorType, BoxType>::
*/



template<typename ValueType, typename VectorType, typename BoxType> Box__<ValueType, VectorType, BoxType>::Box__(VectorType min, VectorType max)
	: Min(min)
	, Max(max)
{ }



template<typename ValueType, typename VectorType, typename BoxType>
VectorType
Box__<ValueType, VectorType, BoxType>::Size() const
{
	return (Max - Min);
}
template<typename ValueType, typename VectorType, typename BoxType>
VectorType
Box__<ValueType, VectorType, BoxType>::Center() const
{
	return ((Max + Min) / 2.0f);
}
