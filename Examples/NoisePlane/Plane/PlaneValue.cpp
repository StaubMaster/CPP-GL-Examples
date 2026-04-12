#include "PlaneValue.hpp"



PlaneValue::~PlaneValue() { }
PlaneValue::PlaneValue()
	: Known(false)
	, Value(0.0f)
{ }
PlaneValue::PlaneValue(const PlaneValue & other)
	: Known(other.Known)
	, Value(other.Value)
{ }
PlaneValue & PlaneValue::operator=(const PlaneValue & other)
{
	Known = other.Known;
	Value = other.Value;
	return *this;
}

ColorF4 PlaneValue::ToColor() const
{
	if (Value > 0.0f) { return ColorF4(+Value, 0, 0); }
	if (Value < 0.0f) { return ColorF4(0, 0, -Value); }
	return ColorF4(0, 0, 0);
}
