#include "ValueType/Vector/U3.hpp"

#include "ValueType/Vector/I3.hpp"
#include "ValueType/Vector/F3.hpp"

#include "ValueType/Bool/3.hpp"



VectorU3::VectorU3(unsigned int x, unsigned int y, unsigned int z)
	: X(x)
	, Y(y)
	, Z(z)
{ }
VectorU3::VectorU3(unsigned int value)
	: X(value)
	, Y(value)
	, Z(value)
{ }

VectorI3 VectorU3::ToI() const { return VectorI3(X, Y, Z); }
VectorF3 VectorU3::ToF() const { return VectorF3(X, Y, Z); }



VectorU3 VectorU3::Min(const VectorU3 & other) const
{
	VectorU3 vec(*this);
	if (other.X < vec.X) { vec.X = other.X; }
	if (other.Y < vec.Y) { vec.Y = other.Y; }
	if (other.Z < vec.Z) { vec.Z = other.Z; }
	return vec;
}
VectorU3 VectorU3::Max(const VectorU3 & other) const
{
	VectorU3 vec(*this);
	if (other.X > vec.X) { vec.X = other.X; }
	if (other.Y > vec.Y) { vec.Y = other.Y; }
	if (other.Z > vec.Z) { vec.Z = other.Z; }
	return vec;
}
VectorU3 VectorU3::Mix(const VectorU3 & other, const Bool3 & condition) const
{
	VectorU3 vec(*this);
	if (condition.GetX()) { vec.X = other.X; }
	if (condition.GetY()) { vec.Y = other.Y; }
	if (condition.GetZ()) { vec.Z = other.Z; }
	return vec;
}

VectorU3 VectorU3::Min(const VectorU3 & vec0, const VectorU3 & vec1)
{
	VectorU3 vec;
	if (vec0.X < vec1.X) { vec.X = vec0.X; } else { vec.X = vec1.X; }
	if (vec0.Y < vec1.Y) { vec.Y = vec0.Y; } else { vec.Y = vec1.Y; }
	if (vec0.Z < vec1.Z) { vec.Z = vec0.Z; } else { vec.Z = vec1.Z; }
	return vec;
}
VectorU3 VectorU3::Max(const VectorU3 & vec0, const VectorU3 & vec1)
{
	VectorU3 vec;
	if (vec0.X > vec1.X) { vec.X = vec0.X; } else { vec.X = vec1.X; }
	if (vec0.Y > vec1.Y) { vec.Y = vec0.Y; } else { vec.Y = vec1.Y; }
	if (vec0.Z > vec1.Z) { vec.Z = vec0.Z; } else { vec.Z = vec1.Z; }
	return vec;
}
VectorU3 VectorU3::Mix(const VectorU3 & vec0, const VectorU3 & vec1, const Bool3 & condition)
{
	VectorU3 vec;
	if (condition.GetX()) { vec.X = vec1.X; } else { vec.X = vec0.X; }
	if (condition.GetY()) { vec.Y = vec1.Y; } else { vec.Y = vec0.Y; }
	if (condition.GetZ()) { vec.Z = vec1.Z; } else { vec.Z = vec0.Z; }
	return vec;
}



unsigned int VectorU3::Product() const { return X * Y * Z; }

unsigned int VectorU3::Convert(VectorU3 udx) const
{
	return (udx.X) + (udx.Y * X) + (udx.Z * X * Y);
}
VectorU3 VectorU3::Convert(unsigned int udx) const
{
	VectorU3 vec;
	vec.X = udx % X; udx = udx / X;
	vec.Y = udx % Y; udx = udx / Y;
//	vec.Z = udx % Z;
	vec.Z = udx;
	return vec;
}

unsigned int VectorU3::Convert(unsigned int size, VectorU3 udx)
{
	return (udx.X) + (udx.Y * size) + (udx.Z * size * size);
}
VectorU3 VectorU3::Convert(unsigned int size, unsigned int udx)
{
	VectorU3 vec;
	vec.X = udx % size; udx = udx / size;
	vec.Y = udx % size; udx = udx / size;
//	vec.Z = udx % size;
	vec.Z = udx;
	return vec;
}



Bool3			VectorU3::operator==(const VectorU3 & other) const	{ return Bool3(X == other.X, Y == other.Y, Z == other.Z); }
Bool3			VectorU3::operator!=(const VectorU3 & other) const	{ return Bool3(X != other.X, Y != other.Y, Z != other.Z); }
Bool3			VectorU3::operator< (const VectorU3 & other) const	{ return Bool3(X <  other.X, Y <  other.Y, Z <  other.Z); }
Bool3			VectorU3::operator> (const VectorU3 & other) const	{ return Bool3(X >  other.X, Y >  other.Y, Z >  other.Z); }
Bool3			VectorU3::operator<=(const VectorU3 & other) const	{ return Bool3(X <= other.X, Y <= other.Y, Z <= other.Z); }
Bool3			VectorU3::operator>=(const VectorU3 & other) const	{ return Bool3(X >= other.X, Y >= other.Y, Z >= other.Z); }

VectorU3		VectorU3::operator+() const							{ return VectorU3(+X, +Y, +Z); }
VectorU3		VectorU3::operator-() const							{ return VectorU3(-X, -Y, -Z); }

VectorU3		VectorU3::operator+(const VectorU3 & other) const	{ return VectorU3(X + other.X, Y + other.Y, Z + other.Z); }
VectorU3		VectorU3::operator-(const VectorU3 & other) const	{ return VectorU3(X - other.X, Y - other.Y, Z - other.Z); }
VectorU3		VectorU3::operator*(const VectorU3 & other) const	{ return VectorU3(X * other.X, Y * other.Y, Z * other.Z); }
VectorU3		VectorU3::operator/(const VectorU3 & other) const	{ return VectorU3(X / other.X, Y / other.Y, Z / other.Z); }

VectorU3		VectorU3::operator%(const VectorU3 & other) const	{ return VectorU3(X % other.X, Y % other.Y, Z % other.Z); }

VectorU3		VectorU3::operator~() const							{ return VectorU3(~X, ~Y, ~Z); }

VectorU3		VectorU3::operator&(const VectorU3 & other) const	{ return VectorU3(X & other.X, Y & other.Y, Z & other.Z); }
VectorU3		VectorU3::operator|(const VectorU3 & other) const	{ return VectorU3(X | other.X, Y | other.Y, Z | other.Z); }
VectorU3		VectorU3::operator^(const VectorU3 & other) const	{ return VectorU3(X ^ other.X, Y ^ other.Y, Z ^ other.Z); }

VectorU3		VectorU3::operator<<(const VectorU3 & other) const	{ return VectorU3(X << other.X, Y << other.Y, Z << other.Z); }
VectorU3		VectorU3::operator>>(const VectorU3 & other) const	{ return VectorU3(X >> other.X, Y >> other.Y, Z >> other.Z); }

VectorU3 &		VectorU3::operator+=(const VectorU3 & other)		{ X += other.X; Y += other.Y; Z += other.Z; return *this; }
VectorU3 &		VectorU3::operator-=(const VectorU3 & other)		{ X -= other.X; Y -= other.Y; Z -= other.Z; return *this; }
VectorU3 &		VectorU3::operator*=(const VectorU3 & other)		{ X *= other.X; Y *= other.Y; Z *= other.Z; return *this; }
VectorU3 &		VectorU3::operator/=(const VectorU3 & other)		{ X /= other.X; Y /= other.Y; Z /= other.Z; return *this; }

VectorU3 &		VectorU3::operator+=(const unsigned int & val)				{ X += val; Y += val; Z += val; return *this; }
VectorU3 &		VectorU3::operator-=(const unsigned int & val)				{ X -= val; Y -= val; Z -= val; return *this; }
VectorU3 &		VectorU3::operator*=(const unsigned int & val)				{ X *= val; Y *= val; Z *= val; return *this; }
VectorU3 &		VectorU3::operator/=(const unsigned int & val)				{ X /= val; Y /= val; Z /= val; return *this; }



VectorU3 	operator+(const VectorU3 & vec, const unsigned int & val) { return VectorU3(vec.X + val, vec.Y + val, vec.Z + val); }
VectorU3 	operator-(const VectorU3 & vec, const unsigned int & val) { return VectorU3(vec.X - val, vec.Y - val, vec.Z - val); }
VectorU3 	operator*(const VectorU3 & vec, const unsigned int & val) { return VectorU3(vec.X * val, vec.Y * val, vec.Z * val); }
VectorU3 	operator/(const VectorU3 & vec, const unsigned int & val) { return VectorU3(vec.X / val, vec.Y / val, vec.Z / val); }

VectorU3 	operator+(const unsigned int & val, const VectorU3 & vec) { return VectorU3(val + vec.X, val + vec.Y, val + vec.Z); }
VectorU3 	operator-(const unsigned int & val, const VectorU3 & vec) { return VectorU3(val - vec.X, val - vec.Y, val - vec.Z); }
VectorU3 	operator*(const unsigned int & val, const VectorU3 & vec) { return VectorU3(val * vec.X, val * vec.Y, val * vec.Z); }
VectorU3 	operator/(const unsigned int & val, const VectorU3 & vec) { return VectorU3(val / vec.X, val / vec.Y, val / vec.Z); }
