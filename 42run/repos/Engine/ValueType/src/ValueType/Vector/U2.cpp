#include "ValueType/Vector/U2.hpp"

#include "ValueType/Vector/I2.hpp"
#include "ValueType/Vector/F2.hpp"

#include "ValueType/Bool/2.hpp"



VectorU2::VectorU2(unsigned int x, unsigned int y)
	: X(x)
	, Y(y)
{ }
VectorU2::VectorU2(unsigned int value)
	: X(value)
	, Y(value)
{ }

VectorI2 VectorU2::ToI() const { return VectorI2(X, Y); }
VectorF2 VectorU2::ToF() const { return VectorF2(X, Y); }



VectorU2 VectorU2::Min(const VectorU2 & other) const
{
	VectorU2 vec(*this);
	if (other.X < vec.X) { vec.X = other.X; }
	if (other.Y < vec.Y) { vec.Y = other.Y; }
	return vec;
}
VectorU2 VectorU2::Max(const VectorU2 & other) const
{
	VectorU2 vec(*this);
	if (other.X > vec.X) { vec.X = other.X; }
	if (other.Y > vec.Y) { vec.Y = other.Y; }
	return vec;
}
VectorU2 VectorU2::Mix(const VectorU2 & other, const Bool2 & condition) const
{
	VectorU2 vec(*this);
	if (condition.GetX()) { vec.X = other.X; }
	if (condition.GetY()) { vec.Y = other.Y; }
	return vec;
}

VectorU2 VectorU2::Min(const VectorU2 & vec0, const VectorU2 & vec1)
{
	VectorU2 vec;
	if (vec0.X < vec1.X) { vec.X = vec0.X; } else { vec.X = vec1.X; }
	if (vec0.Y < vec1.Y) { vec.Y = vec0.Y; } else { vec.Y = vec1.Y; }
	return vec;
}
VectorU2 VectorU2::Max(const VectorU2 & vec0, const VectorU2 & vec1)
{
	VectorU2 vec;
	if (vec0.X > vec1.X) { vec.X = vec0.X; } else { vec.X = vec1.X; }
	if (vec0.Y > vec1.Y) { vec.Y = vec0.Y; } else { vec.Y = vec1.Y; }
	return vec;
}
VectorU2 VectorU2::Mix(const VectorU2 & vec0, const VectorU2 & vec1, const Bool2 & condition)
{
	VectorU2 vec;
	if (condition.GetX()) { vec.X = vec1.X; } else { vec.X = vec0.X; }
	if (condition.GetY()) { vec.Y = vec1.Y; } else { vec.Y = vec0.Y; }
	return vec;
}



unsigned int VectorU2::Product() const { return X * Y; }

unsigned int VectorU2::Convert(VectorU2 udx) const
{
	return (udx.X) + (udx.Y * X);
}
VectorU2 VectorU2::Convert(unsigned int udx) const
{
	VectorU2 vec;
	vec.X = udx % X; udx = udx / X;
//	vec.Y = udx % Z;
	vec.Y = udx;
	return vec;
}

unsigned int VectorU2::Convert(unsigned int size, VectorU2 udx)
{
	return (udx.X) + (udx.Y * size);
}
VectorU2 VectorU2::Convert(unsigned int size, unsigned int udx)
{
	VectorU2 vec;
	vec.X = udx % size; udx = udx / size;
//	vec.Y = udx % size;
	vec.Y = udx;
	return vec;
}



Bool2			VectorU2::operator==(const VectorU2 & other) const	{ return Bool2(X == other.X, Y == other.Y); }
Bool2			VectorU2::operator!=(const VectorU2 & other) const	{ return Bool2(X != other.X, Y != other.Y); }
Bool2			VectorU2::operator< (const VectorU2 & other) const	{ return Bool2(X <  other.X, Y <  other.Y); }
Bool2			VectorU2::operator> (const VectorU2 & other) const	{ return Bool2(X >  other.X, Y >  other.Y); }
Bool2			VectorU2::operator<=(const VectorU2 & other) const	{ return Bool2(X <= other.X, Y <= other.Y); }
Bool2			VectorU2::operator>=(const VectorU2 & other) const	{ return Bool2(X >= other.X, Y >= other.Y); }

VectorU2		VectorU2::operator+() const							{ return VectorU2(+X, +Y); }
VectorU2		VectorU2::operator-() const							{ return VectorU2(-X, -Y); }

VectorU2		VectorU2::operator+(const VectorU2 & other) const	{ return VectorU2(X + other.X, Y + other.Y); }
VectorU2		VectorU2::operator-(const VectorU2 & other) const	{ return VectorU2(X - other.X, Y - other.Y); }
VectorU2		VectorU2::operator*(const VectorU2 & other) const	{ return VectorU2(X * other.X, Y * other.Y); }
VectorU2		VectorU2::operator/(const VectorU2 & other) const	{ return VectorU2(X / other.X, Y / other.Y); }

VectorU2		VectorU2::operator%(const VectorU2 & other) const	{ return VectorU2(X % other.X, Y % other.Y); }

VectorU2		VectorU2::operator~() const							{ return VectorU2(~X, ~Y); }

VectorU2		VectorU2::operator&(const VectorU2 & other) const	{ return VectorU2(X & other.X, Y & other.Y); }
VectorU2		VectorU2::operator|(const VectorU2 & other) const	{ return VectorU2(X | other.X, Y | other.Y); }
VectorU2		VectorU2::operator^(const VectorU2 & other) const	{ return VectorU2(X ^ other.X, Y ^ other.Y); }

VectorU2		VectorU2::operator<<(const VectorU2 & other) const	{ return VectorU2(X << other.X, Y << other.Y); }
VectorU2		VectorU2::operator>>(const VectorU2 & other) const	{ return VectorU2(X >> other.X, Y >> other.Y); }

VectorU2 &		VectorU2::operator+=(const VectorU2 & other)		{ X += other.X; Y += other.Y; return *this; }
VectorU2 &		VectorU2::operator-=(const VectorU2 & other)		{ X -= other.X; Y -= other.Y; return *this; }
VectorU2 &		VectorU2::operator*=(const VectorU2 & other)		{ X *= other.X; Y *= other.Y; return *this; }
VectorU2 &		VectorU2::operator/=(const VectorU2 & other)		{ X /= other.X; Y /= other.Y; return *this; }

VectorU2 &		VectorU2::operator+=(const unsigned int & val)				{ X += val; Y += val; return *this; }
VectorU2 &		VectorU2::operator-=(const unsigned int & val)				{ X -= val; Y -= val; return *this; }
VectorU2 &		VectorU2::operator*=(const unsigned int & val)				{ X *= val; Y *= val; return *this; }
VectorU2 &		VectorU2::operator/=(const unsigned int & val)				{ X /= val; Y /= val; return *this; }



VectorU2 	operator+(const VectorU2 & vec, const unsigned int & val) { return VectorU2(vec.X + val, vec.Y + val); }
VectorU2 	operator-(const VectorU2 & vec, const unsigned int & val) { return VectorU2(vec.X - val, vec.Y - val); }
VectorU2 	operator*(const VectorU2 & vec, const unsigned int & val) { return VectorU2(vec.X * val, vec.Y * val); }
VectorU2 	operator/(const VectorU2 & vec, const unsigned int & val) { return VectorU2(vec.X / val, vec.Y / val); }

VectorU2 	operator+(const unsigned int & val, const VectorU2 & vec) { return VectorU2(val + vec.X, val + vec.Y); }
VectorU2 	operator-(const unsigned int & val, const VectorU2 & vec) { return VectorU2(val - vec.X, val - vec.Y); }
VectorU2 	operator*(const unsigned int & val, const VectorU2 & vec) { return VectorU2(val * vec.X, val * vec.Y); }
VectorU2 	operator/(const unsigned int & val, const VectorU2 & vec) { return VectorU2(val / vec.X, val / vec.Y); }
