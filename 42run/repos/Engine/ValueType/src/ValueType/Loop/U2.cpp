#include "ValueType/Loop/U2.hpp"



LoopU2::LoopU2() :
	Range()
{ }
LoopU2::LoopU2(VectorU2 min, VectorU2 max) :
	Range(min, max),
	MinExclude(false),
	MaxExclude(true)
{ }
LoopU2::LoopU2(VectorU2 min, Bool2 minEx, VectorU2 max, Bool2 maxEx) :
	Range(min, max),
	MinExclude(minEx),
	MaxExclude(maxEx)
{ }
LoopU2::~LoopU2()
{ }

LoopU2::LoopU2(const LoopU2 & other) :
	Range(other.Range)
{ }
LoopU2 & LoopU2::operator=(const LoopU2 & other)
{
	Range = other.Range;
	return *this;
}



VectorU2 LoopU2::Min() const
{
	VectorU2 udx(Range.Min);
	if (MinExclude.GetX()) { udx.X++; }
	if (MinExclude.GetY()) { udx.Y++; }
	return udx;
}
VectorU2 LoopU2::Max() const
{
	VectorU2 udx(Range.Max);
	if (MaxExclude.GetX()) { udx.X--; }
	if (MaxExclude.GetY()) { udx.Y--; }
	return udx;
}



Bool2 LoopU2::Check(VectorU2 udx) const
{
	Bool2 min;
	if (MinExclude.GetX()) { min.SetX(udx.X > Range.Min.X); } else { min.SetX(udx.X >= Range.Min.X); }
	if (MinExclude.GetY()) { min.SetY(udx.Y > Range.Min.Y); } else { min.SetY(udx.Y >= Range.Min.Y); }

	Bool2 max;
	if (MaxExclude.GetX()) { max.SetX(udx.X < Range.Max.X); } else { max.SetX(udx.X <= Range.Max.X); }
	if (MaxExclude.GetY()) { max.SetY(udx.Y < Range.Max.Y); } else { max.SetY(udx.Y <= Range.Max.Y); }

	return min & max;
}



/*	Problem
Overflow might happen
check before ++ and --
*/
void LoopU2::Next(VectorU2 & udx) const
{
	VectorU2	min = Min();
	VectorU2	max = Max();

	if (udx.X >= max.X)
	{
		udx.X = min.X;
		udx.Y++;
	}
	else
	{
		udx.X++;
	}
}
void LoopU2::Prev(VectorU2 & udx) const
{
	udx.X--;
	if (udx.X < Range.Min.X)
	{
		udx.X = Range.Max.X;
		udx.Y--;
	}
}
