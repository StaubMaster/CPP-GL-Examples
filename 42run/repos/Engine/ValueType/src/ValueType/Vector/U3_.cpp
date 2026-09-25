#include "ValueType/Vector/U3.hpp"

#include "ValueType/Vector/F3.hpp"
#include "ValueType/Vector/I3.hpp"



VectorU3::~VectorU3() { }

VectorU3::VectorU3() : Vector_3() { }
VectorU3::VectorU3(unsigned int value) : Vector_3(value) { }
VectorU3::VectorU3(unsigned int x, unsigned int y, unsigned int z) : Vector_3(x, y, z) { }

VectorU3::VectorU3(const VectorU3 & other) : Vector_3(other) { }
VectorU3 & VectorU3::operator=(const VectorU3 & other) { Vector_3::operator=(other); return *this; }



VectorU3 VectorU3::operator%(const VectorU3 & other) const { return VectorU3(X % other.X, Y % other.Y, Z % other.Z); }

VectorU3 VectorU3::operator~() const { return VectorU3(~X, ~Y, ~Z); }
VectorU3 VectorU3::operator&(const VectorU3 & other) const { return VectorU3(X & other.X, Y & other.Y, Z & other.Z); }
VectorU3 VectorU3::operator|(const VectorU3 & other) const { return VectorU3(X | other.X, Y | other.Y, Z | other.Z); }
VectorU3 VectorU3::operator^(const VectorU3 & other) const { return VectorU3(X ^ other.X, Y ^ other.Y, Z ^ other.Z); }
VectorU3 VectorU3::operator<<(const VectorU3 & other) const { return VectorU3(X << other.X, Y << other.Y, Z << other.Z); }
VectorU3 VectorU3::operator>>(const VectorU3 & other) const { return VectorU3(X >> other.X, Y >> other.Y, Z >> other.Z); }



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





VectorU3 operator+(VectorU3 vec, unsigned int val) { return VectorU3(vec.X + val, vec.Y + val, vec.Z + val); }
VectorU3 operator-(VectorU3 vec, unsigned int val) { return VectorU3(vec.X - val, vec.Y - val, vec.Z - val); }
VectorU3 operator*(VectorU3 vec, unsigned int val) { return VectorU3(vec.X * val, vec.Y * val, vec.Z * val); }
VectorU3 operator/(VectorU3 vec, unsigned int val) { return VectorU3(vec.X / val, vec.Y / val, vec.Z / val); }

VectorU3 operator+(unsigned int val, VectorU3 vec) { return VectorU3(val + vec.X, val + vec.Y, val + vec.Z); }
VectorU3 operator-(unsigned int val, VectorU3 vec) { return VectorU3(val - vec.X, val - vec.Y, val - vec.Z); }
VectorU3 operator*(unsigned int val, VectorU3 vec) { return VectorU3(val * vec.X, val * vec.Y, val * vec.Z); }
VectorU3 operator/(unsigned int val, VectorU3 vec) { return VectorU3(val / vec.X, val / vec.Y, val / vec.Z); }
