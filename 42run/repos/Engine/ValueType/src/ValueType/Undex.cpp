#include "ValueType/Undex.hpp"



Undex::~Undex() { }
Undex::Undex()
	: Value(0)
{ }
Undex::Undex(unsigned int val)
	: Value(val)
{ }

Undex::Undex(const Undex & other)
	: Value(other.Value)
{ }
Undex & Undex::operator=(const Undex & other)
{
	Value = other.Value;
	return (*this);
}



bool Undex::IsValid() const { return (Value != 0xFFFFFFFF); }
Undex Undex::Invalid() { return Undex(0xFFFFFFFF); }
Undex::operator bool() const { return IsValid(); }



Undex Undex::operator+(const Undex & other) const { return Undex(Value + other.Value); }
Undex Undex::operator-(const Undex & other) const { return Undex(Value - other.Value); }
Undex Undex::operator*(const Undex & other) const { return Undex(Value * other.Value); }
Undex Undex::operator/(const Undex & other) const { return Undex(Value / other.Value); }
Undex Undex::operator%(const Undex & other) const { return Undex(Value % other.Value); }

Undex Undex::operator+(unsigned int value) const { return Undex(Value + value); }
Undex Undex::operator-(unsigned int value) const { return Undex(Value - value); }
Undex Undex::operator*(unsigned int value) const { return Undex(Value * value); }
Undex Undex::operator/(unsigned int value) const { return Undex(Value / value); }
Undex Undex::operator%(unsigned int value) const { return Undex(Value % value); }

Undex & Undex::operator+=(const Undex & other) { Value += other.Value; return *this; }
Undex & Undex::operator-=(const Undex & other) { Value -= other.Value; return *this; }
Undex & Undex::operator*=(const Undex & other) { Value *= other.Value; return *this; }
Undex & Undex::operator/=(const Undex & other) { Value /= other.Value; return *this; }
Undex & Undex::operator%=(const Undex & other) { Value %= other.Value; return *this; }

Undex & Undex::operator+=(unsigned int value) { Value += value; return *this; }
Undex & Undex::operator-=(unsigned int value) { Value -= value; return *this; }
Undex & Undex::operator*=(unsigned int value) { Value *= value; return *this; }
Undex & Undex::operator/=(unsigned int value) { Value /= value; return *this; }
Undex & Undex::operator%=(unsigned int value) { Value %= value; return *this; }

Undex & Undex::operator++() { Value++; return *this; }
Undex & Undex::operator--() { Value--; return *this; }

Undex Undex::operator++(int) { Undex udx(*this); Value++; return udx; }
Undex Undex::operator--(int) { Undex udx(*this); Value--; return udx; }

bool Undex::operator==(const Undex & other) const { return (Value == other.Value); }
bool Undex::operator<=(const Undex & other) const { return (Value <= other.Value); }
bool Undex::operator>=(const Undex & other) const { return (Value >= other.Value); }
bool Undex::operator!=(const Undex & other) const { return (Value != other.Value); }
bool Undex::operator<(const Undex & other) const { return (Value < other.Value); }
bool Undex::operator>(const Undex & other) const { return (Value > other.Value); }
