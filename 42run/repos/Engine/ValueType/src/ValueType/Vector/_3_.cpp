#include "ValueType/Vector/_3.hpp"
#include "ValueType/Bool/3.hpp"



template<typename ValueType, typename VectorType> Vector_3<ValueType, VectorType>::Vector_3(ValueType value)
	: X(value)
	, Y(value)
	, Z(value)
{ }
template<typename ValueType, typename VectorType> Vector_3<ValueType, VectorType>::Vector_3(ValueType x, ValueType y, ValueType z)
	: X(x)
	, Y(y)
	, Z(z)
{ }

/*template<typename OtherValueType, typename OtherVectorType> Vector_3(const Vector_3<OtherValueType, OtherVectorType> & other)
	: X(other.X)
	, Y(other.Y)
	, Z(other.Z)
{ }*/
/*template<typename OtherValueType, typename OtherVectorType> VectorType & operator=(const Vector_3<OtherValueType, OtherVectorType> & other)
{
	X = other.X;
	Y = other.Y;
	Z = other.Z;
	return *((VectorType*)this);
}*/



template<typename ValueType, typename VectorType> VectorType Vector_3<ValueType, VectorType>::Min(const Vector_3 & other) const
{
	VectorType vec(*this);
	if (other.X < vec.X) { vec.X = other.X; }
	if (other.Y < vec.Y) { vec.Y = other.Y; }
	if (other.Z < vec.Z) { vec.Z = other.Z; }
	return vec;
}
template<typename ValueType, typename VectorType> VectorType Vector_3<ValueType, VectorType>::Max(const Vector_3 & other) const
{
	VectorType vec(*this);
	if (other.X > vec.X) { vec.X = other.X; }
	if (other.Y > vec.Y) { vec.Y = other.Y; }
	if (other.Z > vec.Z) { vec.Z = other.Z; }
	return vec;
}

template<typename ValueType, typename VectorType> VectorType Vector_3<ValueType, VectorType>::Mix(const Bool3 & take, const Vector_3 & other) const
{
	VectorType vec(*this);
	if (take.GetX()) { vec.X = other.X; }
	if (take.GetY()) { vec.Y = other.Y; }
	if (take.GetZ()) { vec.Z = other.Z; }
	return vec;
}
template<typename ValueType, typename VectorType> VectorType Vector_3<ValueType, VectorType>::Mix(const Bool3 & take, const Vector_3 & value_true, const Vector_3 & value_false)
{
	VectorType vec;
	if (take.GetX()) { vec.X = value_true.X; } else { vec.X = value_false.X; }
	if (take.GetY()) { vec.Y = value_true.Y; } else { vec.Y = value_false.Y; }
	if (take.GetZ()) { vec.Z = value_true.Z; } else { vec.Z = value_false.Z; }
	return vec;
}



template<typename ValueType, typename VectorType> VectorType Vector_3<ValueType, VectorType>::operator+() const { return VectorType(+X, +Y, +Z); }
template<typename ValueType, typename VectorType> VectorType Vector_3<ValueType, VectorType>::operator-() const { return VectorType(-X, -Y, -Z); }

template<typename ValueType, typename VectorType> VectorType Vector_3<ValueType, VectorType>::operator+(const Vector_3 & other) const { return VectorType(X + other.X, Y + other.Y, Z + other.Z); }
template<typename ValueType, typename VectorType> VectorType Vector_3<ValueType, VectorType>::operator-(const Vector_3 & other) const { return VectorType(X - other.X, Y - other.Y, Z - other.Z); }
template<typename ValueType, typename VectorType> VectorType Vector_3<ValueType, VectorType>::operator*(const Vector_3 & other) const { return VectorType(X * other.X, Y * other.Y, Z * other.Z); }
template<typename ValueType, typename VectorType> VectorType Vector_3<ValueType, VectorType>::operator/(const Vector_3 & other) const { return VectorType(X / other.X, Y / other.Y, Z / other.Z); }

template<typename ValueType, typename VectorType> VectorType & Vector_3<ValueType, VectorType>::operator+=(const Vector_3 & other) { X += other.X; Y += other.Y; Z += other.Z; return *((VectorType*)this); }
template<typename ValueType, typename VectorType> VectorType & Vector_3<ValueType, VectorType>::operator-=(const Vector_3 & other) { X -= other.X; Y -= other.Y; Z -= other.Z; return *((VectorType*)this); }
template<typename ValueType, typename VectorType> VectorType & Vector_3<ValueType, VectorType>::operator*=(const Vector_3 & other) { X *= other.X; Y *= other.Y; Z *= other.Z; return *((VectorType*)this); }
template<typename ValueType, typename VectorType> VectorType & Vector_3<ValueType, VectorType>::operator/=(const Vector_3 & other) { X /= other.X; Y /= other.Y; Z /= other.Z; return *((VectorType*)this); }

template<typename ValueType, typename VectorType> Bool3 Vector_3<ValueType, VectorType>::operator==(const Vector_3 & other) const { return Bool3(X == other.X, Y == other.Y, Z == other.Z); }
template<typename ValueType, typename VectorType> Bool3 Vector_3<ValueType, VectorType>::operator!=(const Vector_3 & other) const { return Bool3(X != other.X, Y != other.Y, Z != other.Z); }
template<typename ValueType, typename VectorType> Bool3 Vector_3<ValueType, VectorType>::operator< (const Vector_3 & other) const { return Bool3(X <  other.X, Y <  other.Y, Z <  other.Z); }
template<typename ValueType, typename VectorType> Bool3 Vector_3<ValueType, VectorType>::operator> (const Vector_3 & other) const { return Bool3(X >  other.X, Y >  other.Y, Z >  other.Z); }
template<typename ValueType, typename VectorType> Bool3 Vector_3<ValueType, VectorType>::operator<=(const Vector_3 & other) const { return Bool3(X <= other.X, Y <= other.Y, Z <= other.Z); }
template<typename ValueType, typename VectorType> Bool3 Vector_3<ValueType, VectorType>::operator>=(const Vector_3 & other) const { return Bool3(X >= other.X, Y >= other.Y, Z >= other.Z); }

template<typename ValueType, typename VectorType> VectorType & Vector_3<ValueType, VectorType>::operator+=(const ValueType & value) { X += value; Y += value; Z += value; return *((VectorType*)this); }
template<typename ValueType, typename VectorType> VectorType & Vector_3<ValueType, VectorType>::operator-=(const ValueType & value) { X -= value; Y -= value; Z -= value; return *((VectorType*)this); }
template<typename ValueType, typename VectorType> VectorType & Vector_3<ValueType, VectorType>::operator*=(const ValueType & value) { X *= value; Y *= value; Z *= value; return *((VectorType*)this); }
template<typename ValueType, typename VectorType> VectorType & Vector_3<ValueType, VectorType>::operator/=(const ValueType & value) { X /= value; Y /= value; Z /= value; return *((VectorType*)this); }



//template<typename ValueType, typename VectorType> VectorType operator+(const Vector_3<ValueType, VectorType> & vec, const ValueType & val) { return VectorType(vec.X + val, vec.Y + val, vec.Z + val); }
//template<typename ValueType, typename VectorType> VectorType operator-(const Vector_3<ValueType, VectorType> & vec, const ValueType & val) { return VectorType(vec.X - val, vec.Y - val, vec.Z - val); }
//template<typename ValueType, typename VectorType> VectorType operator*(const Vector_3<ValueType, VectorType> & vec, const ValueType & val) { return VectorType(vec.X * val, vec.Y * val, vec.Z * val); }
//template<typename ValueType, typename VectorType> VectorType operator/(const Vector_3<ValueType, VectorType> & vec, const ValueType & val) { return VectorType(vec.X / val, vec.Y / val, vec.Z / val); }
//
//template<typename ValueType, typename VectorType> VectorType operator+(const ValueType & val, const Vector_3<ValueType, VectorType> & vec) { return VectorType(val + vec.X, val + vec.Y, val + vec.Z); }
//template<typename ValueType, typename VectorType> VectorType operator-(const ValueType & val, const Vector_3<ValueType, VectorType> & vec) { return VectorType(val - vec.X, val - vec.Y, val - vec.Z); }
//template<typename ValueType, typename VectorType> VectorType operator*(const ValueType & val, const Vector_3<ValueType, VectorType> & vec) { return VectorType(val * vec.X, val * vec.Y, val * vec.Z); }
//template<typename ValueType, typename VectorType> VectorType operator/(const ValueType & val, const Vector_3<ValueType, VectorType> & vec) { return VectorType(val / vec.X, val / vec.Y, val / vec.Z); }
