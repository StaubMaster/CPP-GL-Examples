#include "ValueType/Bool/3.hpp"



Bool3::Bool3(unsigned char bits) :
	Bits(bits)
{ }



bool Bool3::GetX() const { return (Bits >> 0) & 1; }
bool Bool3::GetY() const { return (Bits >> 1) & 1; }
bool Bool3::GetZ() const { return (Bits >> 2) & 1; }

void Bool3::SetX(bool value) { Bits = (Bits & 0b110) | (value << 0); }
void Bool3::SetY(bool value) { Bits = (Bits & 0b101) | (value << 1); }
void Bool3::SetZ(bool value) { Bits = (Bits & 0b011) | (value << 2); }

bool Bool3::All(bool value) const { return ((GetX() == value) & (GetY() == value) & (GetZ() == value)); }
bool Bool3::Any(bool value) const { return ((GetX() == value) | (GetY() == value) | (GetZ() == value)); }

unsigned char Bool3::Count(bool value) const
{
	unsigned char count = 0;
	count += (GetX() == value);
	count += (GetY() == value);
	count += (GetZ() == value);
	return count;
}



Bool3::~Bool3()
{ }

Bool3::Bool3() :
	Bits(0)
{ }
Bool3::Bool3(bool value) :
	Bits((value << 0) | (value << 1) | (value << 2))
{ }
Bool3::Bool3(bool x, bool y, bool z) :
	Bits((x << 0) | (y << 1) | (z << 2))
{ }

Bool3::Bool3(const Bool3 & other) :
	Bits(other.Bits)
{ }
Bool3 & Bool3::operator=(const Bool3 & other)
{
	Bits = other.Bits;
	return *this;
}



Bool3 Bool3::operator!() const { return Bool3((unsigned char)(~Bits)); }
Bool3 Bool3::operator&(const Bool3 & other) const { return Bool3((unsigned char)(Bits & other.Bits)); }
Bool3 Bool3::operator|(const Bool3 & other) const { return Bool3((unsigned char)(Bits | other.Bits)); }
Bool3 Bool3::operator^(const Bool3 & other) const { return Bool3((unsigned char)(Bits ^ other.Bits)); }

bool Bool3::operator==(const Bool3 & other) const { return Bits == other.Bits; }
bool Bool3::operator!=(const Bool3 & other) const { return Bits != other.Bits; }

bool Bool3::operator&(bool value) const { return ((GetX() == value) & (GetY() == value) & (GetZ() == value)); }
bool Bool3::operator|(bool value) const { return ((GetX() == value) | (GetY() == value) | (GetZ() == value)); }
bool Bool3::operator^(bool value) const { return ((GetX() == value) ^ (GetY() == value) ^ (GetZ() == value)); }
