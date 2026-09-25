#include "ValueType/Loop/U3.hpp"



LoopU3::LoopU3() :
	Range()
{ }
LoopU3::LoopU3(VectorU3 min, VectorU3 max) :
	Range(min, max),
	MinExclude(false),
	MaxExclude(true)
{ }
LoopU3::LoopU3(VectorU3 min, Bool3 minEx, VectorU3 max, Bool3 maxEx) :
	Range(min, max),
	MinExclude(minEx),
	MaxExclude(maxEx)
{ }
LoopU3::~LoopU3()
{ }

LoopU3::LoopU3(const LoopU3 & other) :
	Range(other.Range)
{ }
LoopU3 & LoopU3::operator=(const LoopU3 & other)
{
	Range = other.Range;
	return *this;
}



VectorU3 LoopU3::Min() const
{
	VectorU3 udx(Range.Min);
	if (MinExclude.GetX()) { udx.X++; }
	if (MinExclude.GetY()) { udx.Y++; }
	if (MinExclude.GetZ()) { udx.Z++; }
	return udx;
}
VectorU3 LoopU3::Max() const
{
	VectorU3 udx(Range.Max);
	if (MaxExclude.GetX()) { udx.X--; }
	if (MaxExclude.GetY()) { udx.Y--; }
	if (MaxExclude.GetZ()) { udx.Z--; }
	return udx;
}



Bool3 LoopU3::Check(VectorU3 udx) const
{
	Bool3 min;
	if (MinExclude.GetX()) { min.SetX(udx.X > Range.Min.X); } else { min.SetX(udx.X >= Range.Min.X); }
	if (MinExclude.GetY()) { min.SetY(udx.Y > Range.Min.Y); } else { min.SetY(udx.Y >= Range.Min.Y); }
	if (MinExclude.GetZ()) { min.SetZ(udx.Z > Range.Min.Z); } else { min.SetZ(udx.Z >= Range.Min.Z); }

	Bool3 max;
	if (MaxExclude.GetX()) { max.SetX(udx.X < Range.Max.X); } else { max.SetX(udx.X <= Range.Max.X); }
	if (MaxExclude.GetY()) { max.SetY(udx.Y < Range.Max.Y); } else { max.SetY(udx.Y <= Range.Max.Y); }
	if (MaxExclude.GetZ()) { max.SetZ(udx.Z < Range.Max.Z); } else { max.SetZ(udx.Z <= Range.Max.Z); }

	return min & max;
}



/*	Problem
Overflow might happen
check before ++ and --
*/
void LoopU3::Next(VectorU3 & udx) const
{
	VectorU3	min = Min();
	VectorU3	max = Max();

	if (udx.X >= max.X)
	{
		udx.X = min.X;
		if (udx.Y >= max.Y)
		{
			udx.Y = min.Y;
			udx.Z++;
		}
		else
		{
			udx.Y++;
		}
	}
	else
	{
		udx.X++;
	}
}
void LoopU3::Prev(VectorU3 & udx) const
{
	VectorU3	min = Min();
	VectorU3	max = Max();

	if (udx.X <= min.X)
	{
		udx.X = max.X;
		if (udx.Y <= min.Y)
		{
			udx.Y = max.Y;
			udx.Z--;
		}
		else
		{
			udx.Y--;
		}
	}
	else
	{
		udx.X--;
	}
}
