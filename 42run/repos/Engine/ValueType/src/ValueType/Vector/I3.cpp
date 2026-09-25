#include "ValueType/Vector/I3.hpp"

#include "ValueType/Vector/U3.hpp"
#include "ValueType/Vector/F3.hpp"

#include "ValueType/Bool/3.hpp"



VectorI3::VectorI3(int x, int y, int z)
	: X(x)
	, Y(y)
	, Z(z)
{ }
VectorI3::VectorI3(int value)
	: X(value)
	, Y(value)
	, Z(value)
{ }

VectorU3 VectorI3::ToU() const { return VectorU3(X, Y, Z); }
VectorF3 VectorI3::ToF() const { return VectorF3(X, Y, Z); }



VectorI3 VectorI3::Min(const VectorI3 & other) const
{
	VectorI3 vec(*this);
	if (other.X < vec.X) { vec.X = other.X; }
	if (other.Y < vec.Y) { vec.Y = other.Y; }
	if (other.Z < vec.Z) { vec.Z = other.Z; }
	return vec;
}
VectorI3 VectorI3::Max(const VectorI3 & other) const
{
	VectorI3 vec(*this);
	if (other.X > vec.X) { vec.X = other.X; }
	if (other.Y > vec.Y) { vec.Y = other.Y; }
	if (other.Z > vec.Z) { vec.Z = other.Z; }
	return vec;
}
VectorI3 VectorI3::Mix(const VectorI3 & other, const Bool3 & condition) const
{
	VectorI3 vec(*this);
	if (condition.GetX()) { vec.X = other.X; }
	if (condition.GetY()) { vec.Y = other.Y; }
	if (condition.GetZ()) { vec.Z = other.Z; }
	return vec;
}

VectorI3 VectorI3::Min(const VectorI3 & vec0, const VectorI3 & vec1)
{
	VectorI3 vec;
	if (vec0.X < vec1.X) { vec.X = vec0.X; } else { vec.X = vec1.X; }
	if (vec0.Y < vec1.Y) { vec.Y = vec0.Y; } else { vec.Y = vec1.Y; }
	if (vec0.Z < vec1.Z) { vec.Z = vec0.Z; } else { vec.Z = vec1.Z; }
	return vec;
}
VectorI3 VectorI3::Max(const VectorI3 & vec0, const VectorI3 & vec1)
{
	VectorI3 vec;
	if (vec0.X > vec1.X) { vec.X = vec0.X; } else { vec.X = vec1.X; }
	if (vec0.Y > vec1.Y) { vec.Y = vec0.Y; } else { vec.Y = vec1.Y; }
	if (vec0.Z > vec1.Z) { vec.Z = vec0.Z; } else { vec.Z = vec1.Z; }
	return vec;
}
VectorI3 VectorI3::Mix(const VectorI3 & vec0, const VectorI3 & vec1, const Bool3 & condition)
{
	VectorI3 vec;
	if (condition.GetX()) { vec.X = vec1.X; } else { vec.X = vec0.X; }
	if (condition.GetY()) { vec.Y = vec1.Y; } else { vec.Y = vec0.Y; }
	if (condition.GetZ()) { vec.Z = vec1.Z; } else { vec.Z = vec0.Z; }
	return vec;
}



int VectorI3::Product() const { return X * Y * Z; }

int VectorI3::Convert(VectorI3 idx) const
{
	return (idx.X) + (idx.Y * X) + (idx.Z * X * Y);
}
VectorI3 VectorI3::Convert(int idx) const
{
	VectorI3 vec;
	vec.X = idx % X; idx = idx / X;
	vec.Y = idx % Y; idx = idx / Y;
//	vec.Z = idx % Z;
	vec.Z = idx;
	return vec;
}

int VectorI3::Convert(int size, VectorI3 idx)
{
	return (idx.X) + (idx.Y * size) + (idx.Z * size * size);
}
VectorI3 VectorI3::Convert(int size, int idx)
{
	VectorI3 vec;
	vec.X = idx % size; idx = idx / size;
	vec.Y = idx % size; idx = idx / size;
//	vec.Z = idx % size;
	vec.Z = idx;
	return vec;
}



Bool3			VectorI3::operator==(const VectorI3 & other) const	{ return Bool3(X == other.X, Y == other.Y, Z == other.Z); }
Bool3			VectorI3::operator!=(const VectorI3 & other) const	{ return Bool3(X != other.X, Y != other.Y, Z != other.Z); }
Bool3			VectorI3::operator< (const VectorI3 & other) const	{ return Bool3(X <  other.X, Y <  other.Y, Z <  other.Z); }
Bool3			VectorI3::operator> (const VectorI3 & other) const	{ return Bool3(X >  other.X, Y >  other.Y, Z >  other.Z); }
Bool3			VectorI3::operator<=(const VectorI3 & other) const	{ return Bool3(X <= other.X, Y <= other.Y, Z <= other.Z); }
Bool3			VectorI3::operator>=(const VectorI3 & other) const	{ return Bool3(X >= other.X, Y >= other.Y, Z >= other.Z); }

VectorI3		VectorI3::operator+() const							{ return VectorI3(+X, +Y, +Z); }
VectorI3		VectorI3::operator-() const							{ return VectorI3(-X, -Y, -Z); }

VectorI3		VectorI3::operator+(const VectorI3 & other) const	{ return VectorI3(X + other.X, Y + other.Y, Z + other.Z); }
VectorI3		VectorI3::operator-(const VectorI3 & other) const	{ return VectorI3(X - other.X, Y - other.Y, Z - other.Z); }
VectorI3		VectorI3::operator*(const VectorI3 & other) const	{ return VectorI3(X * other.X, Y * other.Y, Z * other.Z); }
VectorI3		VectorI3::operator/(const VectorI3 & other) const	{ return VectorI3(X / other.X, Y / other.Y, Z / other.Z); }

VectorI3		VectorI3::operator%(const VectorI3 & other) const	{ return VectorI3(X % other.X, Y % other.Y, Z % other.Z); }

VectorI3		VectorI3::operator~() const							{ return VectorI3(~X, ~Y, ~Z); }

VectorI3		VectorI3::operator&(const VectorI3 & other) const	{ return VectorI3(X & other.X, Y & other.Y, Z & other.Z); }
VectorI3		VectorI3::operator|(const VectorI3 & other) const	{ return VectorI3(X | other.X, Y | other.Y, Z | other.Z); }
VectorI3		VectorI3::operator^(const VectorI3 & other) const	{ return VectorI3(X ^ other.X, Y ^ other.Y, Z ^ other.Z); }

VectorI3		VectorI3::operator<<(const VectorI3 & other) const	{ return VectorI3(X << other.X, Y << other.Y, Z << other.Z); }
VectorI3		VectorI3::operator>>(const VectorI3 & other) const	{ return VectorI3(X >> other.X, Y >> other.Y, Z >> other.Z); }

VectorI3 &		VectorI3::operator+=(const VectorI3 & other)		{ X += other.X; Y += other.Y; Z += other.Z; return *this; }
VectorI3 &		VectorI3::operator-=(const VectorI3 & other)		{ X -= other.X; Y -= other.Y; Z -= other.Z; return *this; }
VectorI3 &		VectorI3::operator*=(const VectorI3 & other)		{ X *= other.X; Y *= other.Y; Z *= other.Z; return *this; }
VectorI3 &		VectorI3::operator/=(const VectorI3 & other)		{ X /= other.X; Y /= other.Y; Z /= other.Z; return *this; }

VectorI3 &		VectorI3::operator+=(const int & val)				{ X += val; Y += val; Z += val; return *this; }
VectorI3 &		VectorI3::operator-=(const int & val)				{ X -= val; Y -= val; Z -= val; return *this; }
VectorI3 &		VectorI3::operator*=(const int & val)				{ X *= val; Y *= val; Z *= val; return *this; }
VectorI3 &		VectorI3::operator/=(const int & val)				{ X /= val; Y /= val; Z /= val; return *this; }



VectorI3 	operator+(const VectorI3 & vec, const int & val) { return VectorI3(vec.X + val, vec.Y + val, vec.Z + val); }
VectorI3 	operator-(const VectorI3 & vec, const int & val) { return VectorI3(vec.X - val, vec.Y - val, vec.Z - val); }
VectorI3 	operator*(const VectorI3 & vec, const int & val) { return VectorI3(vec.X * val, vec.Y * val, vec.Z * val); }
VectorI3 	operator/(const VectorI3 & vec, const int & val) { return VectorI3(vec.X / val, vec.Y / val, vec.Z / val); }

VectorI3 	operator+(const int & val, const VectorI3 & vec) { return VectorI3(val + vec.X, val + vec.Y, val + vec.Z); }
VectorI3 	operator-(const int & val, const VectorI3 & vec) { return VectorI3(val - vec.X, val - vec.Y, val - vec.Z); }
VectorI3 	operator*(const int & val, const VectorI3 & vec) { return VectorI3(val * vec.X, val * vec.Y, val * vec.Z); }
VectorI3 	operator/(const int & val, const VectorI3 & vec) { return VectorI3(val / vec.X, val / vec.Y, val / vec.Z); }
