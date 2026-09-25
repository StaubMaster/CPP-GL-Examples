#ifndef  VECTOR_3_HPP
# define VECTOR_3_HPP

//# include "ValueType/Bool/3.hpp"

struct Bool3;

template<typename ValueType, typename VectorType> struct Vector_3
{
ValueType X = 0;
ValueType Y = 0;
ValueType Z = 0;



~Vector_3() = default;
Vector_3() = default;
Vector_3(const Vector_3 & other) = default;
Vector_3 & operator=(const Vector_3 & other) = default;

Vector_3(ValueType value);
Vector_3(ValueType x, ValueType y, ValueType z);

//template<typename OtherValueType, typename OtherVectorType> Vector_3(const Vector_3<OtherValueType, OtherVectorType> & other);
//template<typename OtherValueType, typename OtherVectorType> VectorType & operator=(const Vector_3<OtherValueType, OtherVectorType> & other);



VectorType		Min(const Vector_3 & other) const;
VectorType		Max(const Vector_3 & other) const;

		VectorType	Mix(const Bool3 & take, const Vector_3 & other) const;
static	VectorType	Mix(const Bool3 & take, const Vector_3 & value_true, const Vector_3 & value_false);



VectorType		operator+() const;
VectorType		operator-() const;

VectorType		operator+(const Vector_3 & other) const;
VectorType		operator-(const Vector_3 & other) const;
VectorType		operator*(const Vector_3 & other) const; //
VectorType		operator/(const Vector_3 & other) const;

VectorType &	operator+=(const Vector_3 & other);
VectorType &	operator-=(const Vector_3 & other);
VectorType &	operator*=(const Vector_3 & other);
VectorType &	operator/=(const Vector_3 & other);

Bool3			operator==(const Vector_3 & other) const;
Bool3			operator!=(const Vector_3 & other) const;
Bool3			operator< (const Vector_3 & other) const;
Bool3			operator> (const Vector_3 & other) const;
Bool3			operator<=(const Vector_3 & other) const;
Bool3			operator>=(const Vector_3 & other) const;

VectorType &	operator+=(const ValueType & value);
VectorType &	operator-=(const ValueType & value);
VectorType &	operator*=(const ValueType & value);
VectorType &	operator/=(const ValueType & value);
};

template<typename ValueType, typename VectorType> VectorType		operator+(const Vector_3<ValueType, VectorType> & vec, const ValueType & val);
template<typename ValueType, typename VectorType> VectorType		operator-(const Vector_3<ValueType, VectorType> & vec, const ValueType & val);
template<typename ValueType, typename VectorType> VectorType		operator*(const Vector_3<ValueType, VectorType> & vec, const ValueType & val); //
template<typename ValueType, typename VectorType> VectorType		operator/(const Vector_3<ValueType, VectorType> & vec, const ValueType & val);

template<typename ValueType, typename VectorType> VectorType		operator+(const ValueType & val, const Vector_3<ValueType, VectorType> & vec);
template<typename ValueType, typename VectorType> VectorType		operator-(const ValueType & val, const Vector_3<ValueType, VectorType> & vec);
template<typename ValueType, typename VectorType> VectorType		operator*(const ValueType & val, const Vector_3<ValueType, VectorType> & vec);
template<typename ValueType, typename VectorType> VectorType		operator/(const ValueType & val, const Vector_3<ValueType, VectorType> & vec);

#endif