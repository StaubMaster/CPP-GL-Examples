#include "ValueType/Vector/F3.hpp"

#include "ValueType/Vector/U3.hpp"
#include "ValueType/Vector/I3.hpp"

#include <math.h>



VectorF3::~VectorF3() { }

VectorF3::VectorF3() : Vector_3() { }
VectorF3::VectorF3(float value) : Vector_3(value) { }
VectorF3::VectorF3(float x, float y, float z) : Vector_3(x, y, z) { }

VectorF3::VectorF3(const VectorF3 & other) : Vector_3(other) { }
VectorF3 & VectorF3::operator=(const VectorF3 & other) { Vector_3::operator=(other); return *this; }



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



VectorF3 operator+(VectorF3 v, float f) { return VectorF3(v.X + f, v.Y + f, v.Z + f); }
VectorF3 operator-(VectorF3 v, float f) { return VectorF3(v.X - f, v.Y - f, v.Z - f); }
VectorF3 operator*(VectorF3 v, float f) { return VectorF3(v.X * f, v.Y * f, v.Z * f); }
VectorF3 operator/(VectorF3 v, float f) { return VectorF3(v.X / f, v.Y / f, v.Z / f); }

VectorF3 operator+(float f, VectorF3 v) { return VectorF3(f + v.X, f + v.Y, f + v.Z); }
VectorF3 operator-(float f, VectorF3 v) { return VectorF3(f - v.X, f - v.Y, f - v.Z); }
VectorF3 operator*(float f, VectorF3 v) { return VectorF3(f * v.X, f * v.Y, f * v.Z); }
VectorF3 operator/(float f, VectorF3 v) { return VectorF3(f / v.X, f / v.Y, f / v.Z); }
