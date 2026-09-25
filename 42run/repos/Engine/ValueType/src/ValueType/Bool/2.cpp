#include "ValueType/Bool/2.hpp"



Bool2::Bool2(unsigned char bits) :
	Bits(bits)
{ }



bool Bool2::GetX() const { return (Bits >> 0) & 1; }
bool Bool2::GetY() const { return (Bits >> 1) & 1; }

void Bool2::SetX(bool value) { Bits = (Bits & 0b10) | (value << 0); }
void Bool2::SetY(bool value) { Bits = (Bits & 0b01) | (value << 1); }

bool Bool2::All(bool value) const { return ((GetX() == value) & (GetY() == value)); }
bool Bool2::Any(bool value) const { return ((GetX() == value) | (GetY() == value)); }

unsigned char Bool2::Count(bool value) const
{
	unsigned char count = 0;
	count += (GetX() == value);
	count += (GetY() == value);
	return count;
}



Bool2::~Bool2()
{ }

Bool2::Bool2() :
	Bits(0)
{ }
Bool2::Bool2(bool value) :
	Bits((value << 0) | (value << 1))
{ }
Bool2::Bool2(bool x, bool y) :
	Bits((x << 0) | (y << 1))
{ }

Bool2::Bool2(const Bool2 & other) :
	Bits(other.Bits)
{ }
Bool2 & Bool2::operator=(const Bool2 & other)
{
	Bits = other.Bits;
	return *this;
}



Bool2 Bool2::operator!() const { return Bool2((unsigned char)(~Bits)); }
Bool2 Bool2::operator&(const Bool2 & other) const { return Bool2((unsigned char)(Bits & other.Bits)); }
Bool2 Bool2::operator|(const Bool2 & other) const { return Bool2((unsigned char)(Bits | other.Bits)); }
Bool2 Bool2::operator^(const Bool2 & other) const { return Bool2((unsigned char)(Bits ^ other.Bits)); }

bool Bool2::operator==(const Bool2 & other) const { return Bits == other.Bits; }
bool Bool2::operator!=(const Bool2 & other) const { return Bits != other.Bits; }

bool Bool2::operator&(bool value) const { return ((GetX() == value) & (GetY() == value)); }
bool Bool2::operator|(bool value) const { return ((GetX() == value) | (GetY() == value)); }
bool Bool2::operator^(bool value) const { return ((GetX() == value) ^ (GetY() == value)); }
