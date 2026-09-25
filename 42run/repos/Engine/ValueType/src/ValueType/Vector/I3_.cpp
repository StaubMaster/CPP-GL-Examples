#include "ValueType/Vector/I3.hpp"

#include "ValueType/Vector/F3.hpp"
#include "ValueType/Vector/U3.hpp"



VectorI3::~VectorI3() { }

VectorI3::VectorI3() : Vector_3() { }
VectorI3::VectorI3(int value) : Vector_3(value) { }
VectorI3::VectorI3(int x, int y, int z) : Vector_3(x, y, z) { }

VectorI3::VectorI3(const VectorI3 & other) : Vector_3(other) { }
VectorI3 & VectorI3::operator=(const VectorI3 & other) { Vector_3::operator=(other); return *this; }



VectorI3 VectorI3::operator%(const VectorI3 & other) const { return VectorI3(X % other.X, Y % other.Y, Z % other.Z); }

VectorI3 VectorI3::operator~() const { return VectorI3(~X, ~Y, ~Z); }
VectorI3 VectorI3::operator&(const VectorI3 & other) const { return VectorI3(X & other.X, Y & other.Y, Z & other.Z); }
VectorI3 VectorI3::operator|(const VectorI3 & other) const { return VectorI3(X | other.X, Y | other.Y, Z | other.Z); }
VectorI3 VectorI3::operator^(const VectorI3 & other) const { return VectorI3(X ^ other.X, Y ^ other.Y, Z ^ other.Z); }
VectorI3 VectorI3::operator<<(const VectorI3 & other) const { return VectorI3(X << other.X, Y << other.Y, Z << other.Z); }
VectorI3 VectorI3::operator>>(const VectorI3 & other) const { return VectorI3(X >> other.X, Y >> other.Y, Z >> other.Z); }



int VectorI3::Product() const { return X * Y * Z; }

unsigned int VectorI3::Convert(VectorI3 idx) const
{
	return (idx.X) + (idx.Y * X) + (idx.Z * X * Y);
}
VectorI3 VectorI3::Convert(unsigned int idx) const
{
	VectorI3 vec;
	vec.X = idx % X; idx = idx / X;
	vec.Y = idx % Y; idx = idx / Y;
//	vec.Z = idx % Z;
	vec.Z = idx;
	return vec;
}

unsigned int VectorI3::Convert(unsigned int size, VectorI3 idx)
{
	return (idx.X) + (idx.Y * size) + (idx.Z * size * size);
}
VectorI3 VectorI3::Convert(unsigned int size, unsigned int idx)
{
	VectorI3 vec;
	vec.X = idx % size; idx = idx / size;
	vec.Y = idx % size; idx = idx / size;
//	vec.Z = idx % size;
	vec.Z = idx;
	return vec;
}





VectorI3 operator+(VectorI3 vec, int val) { return VectorI3(vec.X + val, vec.Y + val, vec.Z + val); }
VectorI3 operator-(VectorI3 vec, int val) { return VectorI3(vec.X - val, vec.Y - val, vec.Z - val); }
VectorI3 operator*(VectorI3 vec, int val) { return VectorI3(vec.X * val, vec.Y * val, vec.Z * val); }
VectorI3 operator/(VectorI3 vec, int val) { return VectorI3(vec.X / val, vec.Y / val, vec.Z / val); }

VectorI3 operator+(int val, VectorI3 vec) { return VectorI3(val + vec.X, val + vec.Y, val + vec.Z); }
VectorI3 operator-(int val, VectorI3 vec) { return VectorI3(val - vec.X, val - vec.Y, val - vec.Z); }
VectorI3 operator*(int val, VectorI3 vec) { return VectorI3(val * vec.X, val * vec.Y, val * vec.Z); }
VectorI3 operator/(int val, VectorI3 vec) { return VectorI3(val / vec.X, val / vec.Y, val / vec.Z); }
