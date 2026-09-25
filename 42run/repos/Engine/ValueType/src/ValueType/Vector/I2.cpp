#include "ValueType/Vector/I2.hpp"

#include "ValueType/Vector/U2.hpp"
#include "ValueType/Vector/F2.hpp"

#include "ValueType/Bool/2.hpp"



VectorI2::VectorI2(int x, int y)
	: X(x)
	, Y(y)
{ }
VectorI2::VectorI2(int value)
	: X(value)
	, Y(value)
{ }

VectorU2 VectorI2::ToU() const { return VectorU2(X, Y); }
VectorF2 VectorI2::ToF() const { return VectorF2(X, Y); }



VectorI2 VectorI2::Min(const VectorI2 & other) const
{
	VectorI2 vec(*this);
	if (other.X < vec.X) { vec.X = other.X; }
	if (other.Y < vec.Y) { vec.Y = other.Y; }
	return vec;
}
VectorI2 VectorI2::Max(const VectorI2 & other) const
{
	VectorI2 vec(*this);
	if (other.X > vec.X) { vec.X = other.X; }
	if (other.Y > vec.Y) { vec.Y = other.Y; }
	return vec;
}
VectorI2 VectorI2::Mix(const VectorI2 & other, const Bool2 & condition) const
{
	VectorI2 vec(*this);
	if (condition.GetX()) { vec.X = other.X; }
	if (condition.GetY()) { vec.Y = other.Y; }
	return vec;
}

VectorI2 VectorI2::Min(const VectorI2 & vec0, const VectorI2 & vec1)
{
	VectorI2 vec;
	if (vec0.X < vec1.X) { vec.X = vec0.X; } else { vec.X = vec1.X; }
	if (vec0.Y < vec1.Y) { vec.Y = vec0.Y; } else { vec.Y = vec1.Y; }
	return vec;
}
VectorI2 VectorI2::Max(const VectorI2 & vec0, const VectorI2 & vec1)
{
	VectorI2 vec;
	if (vec0.X > vec1.X) { vec.X = vec0.X; } else { vec.X = vec1.X; }
	if (vec0.Y > vec1.Y) { vec.Y = vec0.Y; } else { vec.Y = vec1.Y; }
	return vec;
}
VectorI2 VectorI2::Mix(const VectorI2 & vec0, const VectorI2 & vec1, const Bool2 & condition)
{
	VectorI2 vec;
	if (condition.GetX()) { vec.X = vec1.X; } else { vec.X = vec0.X; }
	if (condition.GetY()) { vec.Y = vec1.Y; } else { vec.Y = vec0.Y; }
	return vec;
}



int VectorI2::Product() const { return X * Y; }

int VectorI2::Convert(VectorI2 idx) const
{
	return (idx.X) + (idx.Y * X);
}
VectorI2 VectorI2::Convert(int idx) const
{
	VectorI2 vec;
	vec.X = idx % X; idx = idx / X;
//	vec.Y = idx % Y;
	vec.Y = idx;
	return vec;
}

int VectorI2::Convert(int size, VectorI2 idx)
{
	return (idx.X) + (idx.Y * size);
}
VectorI2 VectorI2::Convert(int size, int idx)
{
	VectorI2 vec;
	vec.X = idx % size; idx = idx / size;
//	vec.Y = idx % size;
	vec.Y = idx;
	return vec;
}



Bool2			VectorI2::operator==(const VectorI2 & other) const	{ return Bool2(X == other.X, Y == other.Y); }
Bool2			VectorI2::operator!=(const VectorI2 & other) const	{ return Bool2(X != other.X, Y != other.Y); }
Bool2			VectorI2::operator< (const VectorI2 & other) const	{ return Bool2(X <  other.X, Y <  other.Y); }
Bool2			VectorI2::operator> (const VectorI2 & other) const	{ return Bool2(X >  other.X, Y >  other.Y); }
Bool2			VectorI2::operator<=(const VectorI2 & other) const	{ return Bool2(X <= other.X, Y <= other.Y); }
Bool2			VectorI2::operator>=(const VectorI2 & other) const	{ return Bool2(X >= other.X, Y >= other.Y); }

VectorI2		VectorI2::operator+() const							{ return VectorI2(+X, +Y); }
VectorI2		VectorI2::operator-() const							{ return VectorI2(-X, -Y); }

VectorI2		VectorI2::operator+(const VectorI2 & other) const	{ return VectorI2(X + other.X, Y + other.Y); }
VectorI2		VectorI2::operator-(const VectorI2 & other) const	{ return VectorI2(X - other.X, Y - other.Y); }
VectorI2		VectorI2::operator*(const VectorI2 & other) const	{ return VectorI2(X * other.X, Y * other.Y); }
VectorI2		VectorI2::operator/(const VectorI2 & other) const	{ return VectorI2(X / other.X, Y / other.Y); }

VectorI2		VectorI2::operator%(const VectorI2 & other) const	{ return VectorI2(X % other.X, Y % other.Y); }

VectorI2		VectorI2::operator~() const							{ return VectorI2(~X, ~Y); }

VectorI2		VectorI2::operator&(const VectorI2 & other) const	{ return VectorI2(X & other.X, Y & other.Y); }
VectorI2		VectorI2::operator|(const VectorI2 & other) const	{ return VectorI2(X | other.X, Y | other.Y); }
VectorI2		VectorI2::operator^(const VectorI2 & other) const	{ return VectorI2(X ^ other.X, Y ^ other.Y); }

VectorI2		VectorI2::operator<<(const VectorI2 & other) const	{ return VectorI2(X << other.X, Y << other.Y); }
VectorI2		VectorI2::operator>>(const VectorI2 & other) const	{ return VectorI2(X >> other.X, Y >> other.Y); }

VectorI2 &		VectorI2::operator+=(const VectorI2 & other)		{ X += other.X; Y += other.Y; return *this; }
VectorI2 &		VectorI2::operator-=(const VectorI2 & other)		{ X -= other.X; Y -= other.Y; return *this; }
VectorI2 &		VectorI2::operator*=(const VectorI2 & other)		{ X *= other.X; Y *= other.Y; return *this; }
VectorI2 &		VectorI2::operator/=(const VectorI2 & other)		{ X /= other.X; Y /= other.Y; return *this; }

VectorI2 &		VectorI2::operator+=(const int & val)				{ X += val; Y += val; return *this; }
VectorI2 &		VectorI2::operator-=(const int & val)				{ X -= val; Y -= val; return *this; }
VectorI2 &		VectorI2::operator*=(const int & val)				{ X *= val; Y *= val; return *this; }
VectorI2 &		VectorI2::operator/=(const int & val)				{ X /= val; Y /= val; return *this; }



VectorI2 	operator+(const VectorI2 & vec, const int & val) { return VectorI2(vec.X + val, vec.Y + val); }
VectorI2 	operator-(const VectorI2 & vec, const int & val) { return VectorI2(vec.X - val, vec.Y - val); }
VectorI2 	operator*(const VectorI2 & vec, const int & val) { return VectorI2(vec.X * val, vec.Y * val); }
VectorI2 	operator/(const VectorI2 & vec, const int & val) { return VectorI2(vec.X / val, vec.Y / val); }

VectorI2 	operator+(const int & val, const VectorI2 & vec) { return VectorI2(val + vec.X, val + vec.Y); }
VectorI2 	operator-(const int & val, const VectorI2 & vec) { return VectorI2(val - vec.X, val - vec.Y); }
VectorI2 	operator*(const int & val, const VectorI2 & vec) { return VectorI2(val * vec.X, val * vec.Y); }
VectorI2 	operator/(const int & val, const VectorI2 & vec) { return VectorI2(val / vec.X, val / vec.Y); }
