#include "ValueType/Vector/F2.hpp"

#include "ValueType/Vector/I2.hpp"
#include "ValueType/Vector/U2.hpp"

#include "ValueType/Bool/2.hpp"

#include <math.h>



VectorF2::VectorF2(float x, float y)
	: X(x)
	, Y(y)
{ }
VectorF2::VectorF2(float value)
	: X(value)
	, Y(value)
{ }

VectorI2 VectorF2::ToI() const { return VectorI2(X, Y); }
VectorU2 VectorF2::ToU() const { return VectorU2(X, Y); }



VectorF2 VectorF2::Min(const VectorF2 & other) const
{
	VectorF2 vec(*this);
	if (other.X < vec.X) { vec.X = other.X; }
	if (other.Y < vec.Y) { vec.Y = other.Y; }
	return vec;
}
VectorF2 VectorF2::Max(const VectorF2 & other) const
{
	VectorF2 vec(*this);
	if (other.X > vec.X) { vec.X = other.X; }
	if (other.Y > vec.Y) { vec.Y = other.Y; }
	return vec;
}
VectorF2 VectorF2::Mix(const VectorF2 & other, const Bool2 & condition) const
{
	VectorF2 vec(*this);
	if (condition.GetX()) { vec.X = other.X; }
	if (condition.GetY()) { vec.Y = other.Y; }
	return vec;
}

VectorF2 VectorF2::Min(const VectorF2 & vec0, const VectorF2 & vec1)
{
	VectorF2 vec;
	if (vec0.X < vec1.X) { vec.X = vec0.X; } else { vec.X = vec1.X; }
	if (vec0.Y < vec1.Y) { vec.Y = vec0.Y; } else { vec.Y = vec1.Y; }
	return vec;
}
VectorF2 VectorF2::Max(const VectorF2 & vec0, const VectorF2 & vec1)
{
	VectorF2 vec;
	if (vec0.X > vec1.X) { vec.X = vec0.X; } else { vec.X = vec1.X; }
	if (vec0.Y > vec1.Y) { vec.Y = vec0.Y; } else { vec.Y = vec1.Y; }
	return vec;
}
VectorF2 VectorF2::Mix(const VectorF2 & vec0, const VectorF2 & vec1, const Bool2 & condition)
{
	VectorF2 vec;
	if (condition.GetX()) { vec.X = vec1.X; } else { vec.X = vec0.X; }
	if (condition.GetY()) { vec.Y = vec1.Y; } else { vec.Y = vec0.Y; }
	return vec;
}



float VectorF2::length2() const { return ((X * X) + (Y * Y)); }
float VectorF2::length() const { return sqrt(length2()); }
VectorF2 VectorF2::normalize() const
{
	float len = length();
	if (len > 0.0f)
	{
		return VectorF2(
			X / len,
			Y / len
		);
	}
	return VectorF2();
}
VectorF2 VectorF2::normalize(float & len) const
{
	len = length();
	if (len > 0.0f)
	{
		return VectorF2(
			X / len,
			Y / len
		);
	}
	len = 0.0f;
	return VectorF2();
}
VectorF2 VectorF2::operator!() const { return normalize(); }



VectorF2 VectorF2::round () const { return VectorF2(roundf(X), roundf(Y)); }
VectorF2 VectorF2::roundC() const { return VectorF2( ceilf(X),  ceilf(Y)); }
VectorF2 VectorF2::roundF() const { return VectorF2(floorf(X), floorf(Y)); }

VectorF2 VectorF2::round (float size) const { return VectorF2(roundf(X / size) * size, roundf(Y / size) * size); }
VectorF2 VectorF2::roundC(float size) const { return VectorF2( ceilf(X / size) * size,  ceilf(Y / size) * size); }
VectorF2 VectorF2::roundF(float size) const { return VectorF2(floorf(X / size) * size, floorf(Y / size) * size); }

VectorF2 VectorF2::abs() const
{
	VectorF2 vec(*this);
	if (vec.X < 0) { vec.X = -vec.X; }
	if (vec.Y < 0) { vec.Y = -vec.Y; }
	return vec;
}



float VectorF2::dot(const VectorF2 & p0, const VectorF2 & p1) { return p0.dot(p1); }
float VectorF2::dot(const VectorF2 & other) const { return ((X * other.X) + (Y * other.Y)); }



float VectorF2::cross(const VectorF2 & other) const
{
	return (
		(X * other.Y) -
		(Y * other.X)
	);
}
float VectorF2::cross(const VectorF2 & v0, const VectorF2 & v1)
{
	return (
		(v0.X * v1.Y) -
		(v0.Y * v1.X)
	);
}

VectorF2 VectorF2::cross(float f) const
{
	return VectorF2(
		+(Y * f),
		-(X * f)
	);
}
VectorF2 VectorF2::cross(float f, const VectorF2 & v)
{
/*
+(00 * 0000) -(f0 * p1.Y)
+(f0 * p1.X) -(00 * 0000)
+(00 * p1.Y) -(00 * p1.X)
*/
	return VectorF2(
		-(f * v.Y),
		+(f * v.X)
	);
}
VectorF2 VectorF2::cross(const VectorF2 & v, float f)
{
/*
+(p0.Y * f1) -(0000 * 00)
+(0000 * 00) -(p0.X * f1)
+(p0.X * 00) -(p0.Y * 00)
*/
	return VectorF2(
		+(v.Y * f),
		-(v.X * f)
	);
}



Bool2			VectorF2::operator==(const VectorF2 & other) const	{ return Bool2(X == other.X, Y == other.Y); }
Bool2			VectorF2::operator!=(const VectorF2 & other) const	{ return Bool2(X != other.X, Y != other.Y); }
Bool2			VectorF2::operator< (const VectorF2 & other) const	{ return Bool2(X <  other.X, Y <  other.Y); }
Bool2			VectorF2::operator> (const VectorF2 & other) const	{ return Bool2(X >  other.X, Y >  other.Y); }
Bool2			VectorF2::operator<=(const VectorF2 & other) const	{ return Bool2(X <= other.X, Y <= other.Y); }
Bool2			VectorF2::operator>=(const VectorF2 & other) const	{ return Bool2(X >= other.X, Y >= other.Y); }

VectorF2		VectorF2::operator+() const							{ return VectorF2(+X, +Y); }
VectorF2		VectorF2::operator-() const							{ return VectorF2(-X, -Y); }

VectorF2		VectorF2::operator+(const VectorF2 & other) const	{ return VectorF2(X + other.X, Y + other.Y); }
VectorF2		VectorF2::operator-(const VectorF2 & other) const	{ return VectorF2(X - other.X, Y - other.Y); }
VectorF2		VectorF2::operator*(const VectorF2 & other) const	{ return VectorF2(X * other.X, Y * other.Y); }
VectorF2		VectorF2::operator/(const VectorF2 & other) const	{ return VectorF2(X / other.X, Y / other.Y); }

VectorF2 &		VectorF2::operator+=(const VectorF2 & other)		{ X += other.X; Y += other.Y; return *this; }
VectorF2 &		VectorF2::operator-=(const VectorF2 & other)		{ X -= other.X; Y -= other.Y; return *this; }
VectorF2 &		VectorF2::operator*=(const VectorF2 & other)		{ X *= other.X; Y *= other.Y; return *this; }
VectorF2 &		VectorF2::operator/=(const VectorF2 & other)		{ X /= other.X; Y /= other.Y; return *this; }

VectorF2 &		VectorF2::operator+=(const float & val)				{ X += val; Y += val; return *this; }
VectorF2 &		VectorF2::operator-=(const float & val)				{ X -= val; Y -= val; return *this; }
VectorF2 &		VectorF2::operator*=(const float & val)				{ X *= val; Y *= val; return *this; }
VectorF2 &		VectorF2::operator/=(const float & val)				{ X /= val; Y /= val; return *this; }



VectorF2 	operator+(const VectorF2 & vec, const float & val) { return VectorF2(vec.X + val, vec.Y + val); }
VectorF2 	operator-(const VectorF2 & vec, const float & val) { return VectorF2(vec.X - val, vec.Y - val); }
VectorF2 	operator*(const VectorF2 & vec, const float & val) { return VectorF2(vec.X * val, vec.Y * val); }
VectorF2 	operator/(const VectorF2 & vec, const float & val) { return VectorF2(vec.X / val, vec.Y / val); }

VectorF2 	operator+(const float & val, const VectorF2 & vec) { return VectorF2(val + vec.X, val + vec.Y); }
VectorF2 	operator-(const float & val, const VectorF2 & vec) { return VectorF2(val - vec.X, val - vec.Y); }
VectorF2 	operator*(const float & val, const VectorF2 & vec) { return VectorF2(val * vec.X, val * vec.Y); }
VectorF2 	operator/(const float & val, const VectorF2 & vec) { return VectorF2(val / vec.X, val / vec.Y); }
