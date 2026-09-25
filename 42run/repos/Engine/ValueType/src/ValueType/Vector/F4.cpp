#include "ValueType/Vector/F4.hpp"

#include "ValueType/Bool/4.hpp"

#include <math.h>



VectorF4::VectorF4(float x, float y, float z, float w)
	: X(x)
	, Y(y)
	, Z(z)
	, W(w)
{ }
VectorF4::VectorF4(float value)
	: X(value)
	, Y(value)
	, Z(value)
	, W(value)
{ }

//VectorI4 VectorF4::ToI() const { return VectorI4(X, Y, Z, W); }
//VectorU4 VectorF4::ToU() const { return VectorU4(X, Y, Z, W); }



VectorF4 VectorF4::Min(const VectorF4 & other) const
{
	VectorF4 vec(*this);
	if (other.X < vec.X) { vec.X = other.X; }
	if (other.Y < vec.Y) { vec.Y = other.Y; }
	if (other.Z < vec.Z) { vec.Z = other.Z; }
	if (other.W < vec.W) { vec.W = other.W; }
	return vec;
}
VectorF4 VectorF4::Max(const VectorF4 & other) const
{
	VectorF4 vec(*this);
	if (other.X > vec.X) { vec.X = other.X; }
	if (other.Y > vec.Y) { vec.Y = other.Y; }
	if (other.Z > vec.Z) { vec.Z = other.Z; }
	if (other.W > vec.W) { vec.W = other.W; }
	return vec;
}
VectorF4 VectorF4::Mix(const VectorF4 & other, const Bool4 & condition) const
{
	VectorF4 vec(*this);
	if (condition.GetX()) { vec.X = other.X; }
	if (condition.GetY()) { vec.Y = other.Y; }
	if (condition.GetZ()) { vec.Z = other.Z; }
	if (condition.GetW()) { vec.W = other.W; }
	return vec;
}

VectorF4 VectorF4::Min(const VectorF4 & vec0, const VectorF4 & vec1)
{
	VectorF4 vec;
	if (vec0.X < vec1.X) { vec.X = vec0.X; } else { vec.X = vec1.X; }
	if (vec0.Y < vec1.Y) { vec.Y = vec0.Y; } else { vec.Y = vec1.Y; }
	if (vec0.Z < vec1.Z) { vec.Z = vec0.Z; } else { vec.Z = vec1.Z; }
	if (vec0.W < vec1.W) { vec.W = vec0.W; } else { vec.W = vec1.W; }
	return vec;
}
VectorF4 VectorF4::Max(const VectorF4 & vec0, const VectorF4 & vec1)
{
	VectorF4 vec;
	if (vec0.X > vec1.X) { vec.X = vec0.X; } else { vec.X = vec1.X; }
	if (vec0.Y > vec1.Y) { vec.Y = vec0.Y; } else { vec.Y = vec1.Y; }
	if (vec0.Z > vec1.Z) { vec.Z = vec0.Z; } else { vec.Z = vec1.Z; }
	if (vec0.W > vec1.W) { vec.W = vec0.W; } else { vec.W = vec1.W; }
	return vec;
}
VectorF4 VectorF4::Mix(const VectorF4 & vec0, const VectorF4 & vec1, const Bool4 & condition)
{
	VectorF4 vec;
	if (condition.GetX()) { vec.X = vec1.X; } else { vec.X = vec0.X; }
	if (condition.GetY()) { vec.Y = vec1.Y; } else { vec.Y = vec0.Y; }
	if (condition.GetZ()) { vec.Z = vec1.Z; } else { vec.Z = vec0.Z; }
	if (condition.GetW()) { vec.W = vec1.W; } else { vec.W = vec0.W; }
	return vec;
}



float VectorF4::length2() const { return ((X * X) + (Y * Y) + (Z * Z) + (W * W)); }
float VectorF4::length() const { return sqrt(length2()); }
VectorF4 VectorF4::normalize() const
{
	float len = length();
	if (len > 0.0f)
	{
		return VectorF4(
			X / len,
			Y / len,
			Z / len,
			W / len
		);
	}
	return VectorF4();
}
VectorF4 VectorF4::normalize(float & len) const
{
	len = length();
	if (len > 0.0f)
	{
		return VectorF4(
			X / len,
			Y / len,
			Z / len,
			W / len
		);
	}
	len = 0.0f;
	return VectorF4();
}
VectorF4 VectorF4::operator!() const { return normalize(); }



VectorF4 VectorF4::round () const { return VectorF4(roundf(X), roundf(Y), roundf(Z), roundf(W)); }
VectorF4 VectorF4::roundC() const { return VectorF4( ceilf(X),  ceilf(Y),  ceilf(Z),  ceilf(W)); }
VectorF4 VectorF4::roundF() const { return VectorF4(floorf(X), floorf(Y), floorf(Z), floorf(W)); }

VectorF4 VectorF4::round (float size) const { return VectorF4(roundf(X / size) * size, roundf(Y / size) * size, roundf(Z / size) * size, roundf(W / size) * size); }
VectorF4 VectorF4::roundC(float size) const { return VectorF4( ceilf(X / size) * size,  ceilf(Y / size) * size,  ceilf(Z / size) * size,  ceilf(W / size) * size); }
VectorF4 VectorF4::roundF(float size) const { return VectorF4(floorf(X / size) * size, floorf(Y / size) * size, floorf(Z / size) * size, floorf(W / size) * size); }

VectorF4 VectorF4::abs() const
{
	VectorF4 vec(*this);
	if (vec.X < 0) { vec.X = -vec.X; }
	if (vec.Y < 0) { vec.Y = -vec.Y; }
	if (vec.Z < 0) { vec.Z = -vec.Z; }
	if (vec.W < 0) { vec.W = -vec.W; }
	return vec;
}



float VectorF4::dot(const VectorF4 & p0, const VectorF4 & p1) { return p0.dot(p1); }
float VectorF4::dot(const VectorF4 & other) const { return ((X * other.X) + (Y * other.Y) + (Z * other.Z) + (W * other.W)); }



Bool4			VectorF4::operator==(const VectorF4 & other) const	{ return Bool4(X == other.X, Y == other.Y, Z == other.Z, W == other.W); }
Bool4			VectorF4::operator!=(const VectorF4 & other) const	{ return Bool4(X != other.X, Y != other.Y, Z != other.Z, W != other.W); }
Bool4			VectorF4::operator< (const VectorF4 & other) const	{ return Bool4(X <  other.X, Y <  other.Y, Z <  other.Z, W <  other.W); }
Bool4			VectorF4::operator> (const VectorF4 & other) const	{ return Bool4(X >  other.X, Y >  other.Y, Z >  other.Z, W >  other.W); }
Bool4			VectorF4::operator<=(const VectorF4 & other) const	{ return Bool4(X <= other.X, Y <= other.Y, Z <= other.Z, W <= other.W); }
Bool4			VectorF4::operator>=(const VectorF4 & other) const	{ return Bool4(X >= other.X, Y >= other.Y, Z >= other.Z, W >= other.W); }

VectorF4		VectorF4::operator+() const							{ return VectorF4(+X, +Y, +Z, +W); }
VectorF4		VectorF4::operator-() const							{ return VectorF4(-X, -Y, -Z, -W); }

VectorF4		VectorF4::operator+(const VectorF4 & other) const	{ return VectorF4(X + other.X, Y + other.Y, Z + other.Z, W + other.W); }
VectorF4		VectorF4::operator-(const VectorF4 & other) const	{ return VectorF4(X - other.X, Y - other.Y, Z - other.Z, W - other.W); }
VectorF4		VectorF4::operator*(const VectorF4 & other) const	{ return VectorF4(X * other.X, Y * other.Y, Z * other.Z, W * other.W); }
VectorF4		VectorF4::operator/(const VectorF4 & other) const	{ return VectorF4(X / other.X, Y / other.Y, Z / other.Z, W / other.W); }

VectorF4 &		VectorF4::operator+=(const VectorF4 & other)		{ X += other.X; Y += other.Y; Z += other.Z; W += other.W; return *this; }
VectorF4 &		VectorF4::operator-=(const VectorF4 & other)		{ X -= other.X; Y -= other.Y; Z -= other.Z; W -= other.W; return *this; }
VectorF4 &		VectorF4::operator*=(const VectorF4 & other)		{ X *= other.X; Y *= other.Y; Z *= other.Z; W *= other.W; return *this; }
VectorF4 &		VectorF4::operator/=(const VectorF4 & other)		{ X /= other.X; Y /= other.Y; Z /= other.Z; W /= other.W; return *this; }

VectorF4 &		VectorF4::operator+=(const float & val)				{ X += val; Y += val; Z += val; W += val; return *this; }
VectorF4 &		VectorF4::operator-=(const float & val)				{ X -= val; Y -= val; Z -= val; W -= val; return *this; }
VectorF4 &		VectorF4::operator*=(const float & val)				{ X *= val; Y *= val; Z *= val; W *= val; return *this; }
VectorF4 &		VectorF4::operator/=(const float & val)				{ X /= val; Y /= val; Z /= val; W /= val; return *this; }



VectorF4 	operator+(const VectorF4 & vec, const float & val) { return VectorF4(vec.X + val, vec.Y + val, vec.Z + val, vec.W + val); }
VectorF4 	operator-(const VectorF4 & vec, const float & val) { return VectorF4(vec.X - val, vec.Y - val, vec.Z - val, vec.W - val); }
VectorF4 	operator*(const VectorF4 & vec, const float & val) { return VectorF4(vec.X * val, vec.Y * val, vec.Z * val, vec.W * val); }
VectorF4 	operator/(const VectorF4 & vec, const float & val) { return VectorF4(vec.X / val, vec.Y / val, vec.Z / val, vec.W / val); }

VectorF4 	operator+(const float & val, const VectorF4 & vec) { return VectorF4(val + vec.X, val + vec.Y, val + vec.Z, val + vec.W); }
VectorF4 	operator-(const float & val, const VectorF4 & vec) { return VectorF4(val - vec.X, val - vec.Y, val - vec.Z, val - vec.W); }
VectorF4 	operator*(const float & val, const VectorF4 & vec) { return VectorF4(val * vec.X, val * vec.Y, val * vec.Z, val * vec.W); }
VectorF4 	operator/(const float & val, const VectorF4 & vec) { return VectorF4(val / vec.X, val / vec.Y, val / vec.Z, val / vec.W); }
