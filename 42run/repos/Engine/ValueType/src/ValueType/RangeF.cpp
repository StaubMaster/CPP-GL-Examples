#include "ValueType/RangeF.hpp"



RangeF::RangeF(float min, float max)
	: Min(min)
	, Len(max - min)
	, Max(max)
{ }



float RangeF::GetMin() const { return Min; }
float RangeF::GetMax() const { return Max; }

void RangeF::SetMin(float min)
{
	Min = min;
	Len = Max - min;
}
void RangeF::SetMax(float max)
{
	Len = max - Min;
	Max = max;
}



float RangeF::Length() const { return Len; }

void RangeF::MinLength(float len)
{
	Len = len;
	Max = Min + len;
}
void RangeF::MaxLength(float len)
{
	Len = len;
	Min = Max - len;
}
