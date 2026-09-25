#include "ValueType/Bool/4.hpp"



Bool4::Bool4(unsigned char bits) :
	Bits(bits)
{ }



bool Bool4::GetX() const { return (Bits >> 0) & 1; }
bool Bool4::GetY() const { return (Bits >> 1) & 1; }
bool Bool4::GetZ() const { return (Bits >> 2) & 1; }
bool Bool4::GetW() const { return (Bits >> 3) & 1; }

void Bool4::SetX(bool value) { Bits = (Bits & 0b1110) | (value << 0); }
void Bool4::SetY(bool value) { Bits = (Bits & 0b1101) | (value << 1); }
void Bool4::SetZ(bool value) { Bits = (Bits & 0b1011) | (value << 2); }
void Bool4::SetW(bool value) { Bits = (Bits & 0b0111) | (value << 3); }

bool Bool4::All(bool value) const { return ((GetX() == value) & (GetY() == value) & (GetZ() == value) & (GetW() == value)); }
bool Bool4::Any(bool value) const { return ((GetX() == value) | (GetY() == value) | (GetZ() == value) | (GetW() == value)); }

unsigned char Bool4::Count(bool value) const
{
	unsigned char count = 0;
	count += (GetX() == value);
	count += (GetY() == value);
	count += (GetZ() == value);
	count += (GetW() == value);
	return count;
}



Bool4::~Bool4()
{ }

Bool4::Bool4() :
	Bits(0)
{ }
Bool4::Bool4(bool value) :
	Bits((value << 0) | (value << 1) | (value << 2) | (value << 3))
{ }
Bool4::Bool4(bool x, bool y, bool z, bool w) :
	Bits((x << 0) | (y << 1) | (z << 2) | (w << 3))
{ }

Bool4::Bool4(const Bool4 & other) :
	Bits(other.Bits)
{ }
Bool4 & Bool4::operator=(const Bool4 & other)
{
	Bits = other.Bits;
	return *this;
}



Bool4 Bool4::operator!() const { return Bool4((unsigned char)(~Bits)); }
Bool4 Bool4::operator&(const Bool4 & other) const { return Bool4((unsigned char)(Bits & other.Bits)); }
Bool4 Bool4::operator|(const Bool4 & other) const { return Bool4((unsigned char)(Bits | other.Bits)); }
Bool4 Bool4::operator^(const Bool4 & other) const { return Bool4((unsigned char)(Bits ^ other.Bits)); }

bool Bool4::operator==(const Bool4 & other) const { return Bits == other.Bits; }
bool Bool4::operator!=(const Bool4 & other) const { return Bits != other.Bits; }

bool Bool4::operator&(bool value) const { return ((GetX() == value) & (GetY() == value) & (GetZ() == value) & (GetW() == value)); }
bool Bool4::operator|(bool value) const { return ((GetX() == value) | (GetY() == value) | (GetZ() == value) | (GetW() == value)); }
bool Bool4::operator^(bool value) const { return ((GetX() == value) ^ (GetY() == value) ^ (GetZ() == value) ^ (GetW() == value)); }
