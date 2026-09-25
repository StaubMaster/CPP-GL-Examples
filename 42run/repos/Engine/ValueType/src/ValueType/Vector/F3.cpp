#include "ValueType/Vector/F3.hpp"

#include "ValueType/Vector/I3.hpp"
#include "ValueType/Vector/U3.hpp"

#include "ValueType/Bool/3.hpp"

#include <math.h>



VectorF3::VectorF3(float x, float y, float z)
	: X(x)
	, Y(y)
	, Z(z)
{ }
VectorF3::VectorF3(float value)
	: X(value)
	, Y(value)
	, Z(value)
{ }

VectorI3 VectorF3::ToI() const { return VectorI3(X, Y, Z); }
VectorU3 VectorF3::ToU() const { return VectorU3(X, Y, Z); }



VectorF3 VectorF3::Min(const VectorF3 & other) const
{
	VectorF3 vec(*this);
	if (other.X < vec.X) { vec.X = other.X; }
	if (other.Y < vec.Y) { vec.Y = other.Y; }
	if (other.Z < vec.Z) { vec.Z = other.Z; }
	return vec;
}
VectorF3 VectorF3::Max(const VectorF3 & other) const
{
	VectorF3 vec(*this);
	if (other.X > vec.X) { vec.X = other.X; }
	if (other.Y > vec.Y) { vec.Y = other.Y; }
	if (other.Z > vec.Z) { vec.Z = other.Z; }
	return vec;
}
VectorF3 VectorF3::Mix(const VectorF3 & other, const Bool3 & condition) const
{
	VectorF3 vec(*this);
	if (condition.GetX()) { vec.X = other.X; }
	if (condition.GetY()) { vec.Y = other.Y; }
	if (condition.GetZ()) { vec.Z = other.Z; }
	return vec;
}

VectorF3 VectorF3::Min(const VectorF3 & vec0, const VectorF3 & vec1)
{
	VectorF3 vec;
	if (vec0.X < vec1.X) { vec.X = vec0.X; } else { vec.X = vec1.X; }
	if (vec0.Y < vec1.Y) { vec.Y = vec0.Y; } else { vec.Y = vec1.Y; }
	if (vec0.Z < vec1.Z) { vec.Z = vec0.Z; } else { vec.Z = vec1.Z; }
	return vec;
}
VectorF3 VectorF3::Max(const VectorF3 & vec0, const VectorF3 & vec1)
{
	VectorF3 vec;
	if (vec0.X > vec1.X) { vec.X = vec0.X; } else { vec.X = vec1.X; }
	if (vec0.Y > vec1.Y) { vec.Y = vec0.Y; } else { vec.Y = vec1.Y; }
	if (vec0.Z > vec1.Z) { vec.Z = vec0.Z; } else { vec.Z = vec1.Z; }
	return vec;
}
VectorF3 VectorF3::Mix(const VectorF3 & vec0, const VectorF3 & vec1, const Bool3 & condition)
{
	VectorF3 vec;
	if (condition.GetX()) { vec.X = vec1.X; } else { vec.X = vec0.X; }
	if (condition.GetY()) { vec.Y = vec1.Y; } else { vec.Y = vec0.Y; }
	if (condition.GetZ()) { vec.Z = vec1.Z; } else { vec.Z = vec0.Z; }
	return vec;
}



float VectorF3::length2() const { return ((X * X) + (Y * Y) + (Z * Z)); }
float VectorF3::length() const { return sqrt(length2()); }
VectorF3 VectorF3::normalize() const
{
	float len = length();
	if (len > 0.0f)
	{
		return VectorF3(
			X / len,
			Y / len,
			Z / len
		);
	}
	return VectorF3();
}
VectorF3 VectorF3::normalize(float & len) const
{
	len = length();
	if (len > 0.0f)
	{
		return VectorF3(
			X / len,
			Y / len,
			Z / len
		);
	}
	len = 0.0f;
	return VectorF3();
}
VectorF3 VectorF3::operator!() const { return normalize(); }



VectorF3 VectorF3::round () const { return VectorF3(roundf(X), roundf(Y), roundf(Z)); }
VectorF3 VectorF3::roundC() const { return VectorF3( ceilf(X),  ceilf(Y),  ceilf(Z)); }
VectorF3 VectorF3::roundF() const { return VectorF3(floorf(X), floorf(Y), floorf(Z)); }

VectorF3 VectorF3::round (float size) const { return VectorF3(roundf(X / size) * size, roundf(Y / size) * size, roundf(Z / size) * size); }
VectorF3 VectorF3::roundC(float size) const { return VectorF3( ceilf(X / size) * size,  ceilf(Y / size) * size,  ceilf(Z / size) * size); }
VectorF3 VectorF3::roundF(float size) const { return VectorF3(floorf(X / size) * size, floorf(Y / size) * size, floorf(Z / size) * size); }

VectorF3 VectorF3::abs() const
{
	VectorF3 vec(*this);
	if (vec.X < 0) { vec.X = -vec.X; }
	if (vec.Y < 0) { vec.Y = -vec.Y; }
	if (vec.Z < 0) { vec.Z = -vec.Z; }
	return vec;
}



float VectorF3::dot(const VectorF3 & p0, const VectorF3 & p1) { return p0.dot(p1); }
float VectorF3::dot(const VectorF3 & other) const { return ((X * other.X) + (Y * other.Y) + (Z * other.Z)); }



VectorF3 VectorF3::cross(const VectorF3 & p0, const VectorF3 & p1)
{
	return VectorF3(
		(p0.Y * p1.Z) - (p0.Z * p1.Y),
		(p0.Z * p1.X) - (p0.X * p1.Z),
		(p0.X * p1.Y) - (p0.Y * p1.X)
	);
}
VectorF3 VectorF3::cross(const VectorF3 & other) const
{
	return cross(*this, other);
}



VectorI3 VectorF3::RankDimensions() const
{
	VectorI3 ranks;

	const float *	value_ptr = (const float*)this;
	int *			ranks_ptr = (int*)&ranks;

	for (unsigned int i = 0; i < 3; i++)
	{
		if (value_ptr[i] != value_ptr[i])
		{
			ranks_ptr[i] = -1;
		}
		else
		{
			for (unsigned int j = 0; j < 3; j++)
			{
				if (i != j)
				{
					if (value_ptr[i] > value_ptr[j])
					{
						ranks_ptr[i]++;
					}
				}
			}
		}
	}

	return ranks;
}



Bool3			VectorF3::operator==(const VectorF3 & other) const	{ return Bool3(X == other.X, Y == other.Y, Z == other.Z); }
Bool3			VectorF3::operator!=(const VectorF3 & other) const	{ return Bool3(X != other.X, Y != other.Y, Z != other.Z); }
Bool3			VectorF3::operator< (const VectorF3 & other) const	{ return Bool3(X <  other.X, Y <  other.Y, Z <  other.Z); }
Bool3			VectorF3::operator> (const VectorF3 & other) const	{ return Bool3(X >  other.X, Y >  other.Y, Z >  other.Z); }
Bool3			VectorF3::operator<=(const VectorF3 & other) const	{ return Bool3(X <= other.X, Y <= other.Y, Z <= other.Z); }
Bool3			VectorF3::operator>=(const VectorF3 & other) const	{ return Bool3(X >= other.X, Y >= other.Y, Z >= other.Z); }

VectorF3		VectorF3::operator+() const							{ return VectorF3(+X, +Y, +Z); }
VectorF3		VectorF3::operator-() const							{ return VectorF3(-X, -Y, -Z); }

VectorF3		VectorF3::operator+(const VectorF3 & other) const	{ return VectorF3(X + other.X, Y + other.Y, Z + other.Z); }
VectorF3		VectorF3::operator-(const VectorF3 & other) const	{ return VectorF3(X - other.X, Y - other.Y, Z - other.Z); }
VectorF3		VectorF3::operator*(const VectorF3 & other) const	{ return VectorF3(X * other.X, Y * other.Y, Z * other.Z); }
VectorF3		VectorF3::operator/(const VectorF3 & other) const	{ return VectorF3(X / other.X, Y / other.Y, Z / other.Z); }

VectorF3 &		VectorF3::operator+=(const VectorF3 & other)		{ X += other.X; Y += other.Y; Z += other.Z; return *this; }
VectorF3 &		VectorF3::operator-=(const VectorF3 & other)		{ X -= other.X; Y -= other.Y; Z -= other.Z; return *this; }
VectorF3 &		VectorF3::operator*=(const VectorF3 & other)		{ X *= other.X; Y *= other.Y; Z *= other.Z; return *this; }
VectorF3 &		VectorF3::operator/=(const VectorF3 & other)		{ X /= other.X; Y /= other.Y; Z /= other.Z; return *this; }

VectorF3 &		VectorF3::operator+=(const float & val)				{ X += val; Y += val; Z += val; return *this; }
VectorF3 &		VectorF3::operator-=(const float & val)				{ X -= val; Y -= val; Z -= val; return *this; }
VectorF3 &		VectorF3::operator*=(const float & val)				{ X *= val; Y *= val; Z *= val; return *this; }
VectorF3 &		VectorF3::operator/=(const float & val)				{ X /= val; Y /= val; Z /= val; return *this; }



VectorF3 	operator+(const VectorF3 & vec, const float & val) { return VectorF3(vec.X + val, vec.Y + val, vec.Z + val); }
VectorF3 	operator-(const VectorF3 & vec, const float & val) { return VectorF3(vec.X - val, vec.Y - val, vec.Z - val); }
VectorF3 	operator*(const VectorF3 & vec, const float & val) { return VectorF3(vec.X * val, vec.Y * val, vec.Z * val); }
VectorF3 	operator/(const VectorF3 & vec, const float & val) { return VectorF3(vec.X / val, vec.Y / val, vec.Z / val); }

VectorF3 	operator+(const float & val, const VectorF3 & vec) { return VectorF3(val + vec.X, val + vec.Y, val + vec.Z); }
VectorF3 	operator-(const float & val, const VectorF3 & vec) { return VectorF3(val - vec.X, val - vec.Y, val - vec.Z); }
VectorF3 	operator*(const float & val, const VectorF3 & vec) { return VectorF3(val * vec.X, val * vec.Y, val * vec.Z); }
VectorF3 	operator/(const float & val, const VectorF3 & vec) { return VectorF3(val / vec.X, val / vec.Y, val / vec.Z); }
