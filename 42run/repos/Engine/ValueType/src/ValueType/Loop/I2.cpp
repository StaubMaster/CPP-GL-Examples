#include "ValueType/Loop/I2.hpp"



LoopI2::~LoopI2()
{ }

LoopI2::LoopI2() :
	Range()
{ }
LoopI2::LoopI2(VectorI2 min, VectorI2 max) :
	Range(min, max),
	MinExclude(false),
	MaxExclude(true)
{ }
LoopI2::LoopI2(VectorI2 min, Bool2 minEx, VectorI2 max, Bool2 maxEx) :
	Range(min, max),
	MinExclude(minEx),
	MaxExclude(maxEx)
{ }

LoopI2::LoopI2(const LoopI2 & other) :
	Range(other.Range)
{ }
LoopI2 & LoopI2::operator=(const LoopI2 & other)
{
	Range = other.Range;
	return *this;
}



VectorI2 LoopI2::Min() const
{
	VectorI2 idx(Range.Min);
	if (MinExclude.GetX()) { idx.X++; }
	if (MinExclude.GetY()) { idx.Y++; }
	return idx;
}
VectorI2 LoopI2::Max() const
{
	VectorI2 idx(Range.Max);
	if (MaxExclude.GetX()) { idx.X--; }
	if (MaxExclude.GetY()) { idx.Y--; }
	return idx;
}
VectorI2 LoopI2::Size() const
{
	return (Min() - Max());
}



Bool2 LoopI2::Check(VectorI2 idx) const
{
	Bool2 min;
	if (MinExclude.GetX()) { min.SetX(idx.X > Range.Min.X); } else { min.SetX(idx.X >= Range.Min.X); }
	if (MinExclude.GetY()) { min.SetY(idx.Y > Range.Min.Y); } else { min.SetY(idx.Y >= Range.Min.Y); }

	Bool2 max;
	if (MaxExclude.GetX()) { max.SetX(idx.X < Range.Max.X); } else { max.SetX(idx.X <= Range.Max.X); }
	if (MaxExclude.GetY()) { max.SetY(idx.Y < Range.Max.Y); } else { max.SetY(idx.Y <= Range.Max.Y); }

	return min & max;
}



/*	Problem
Overflow might happen
check before ++ and --
*/
void LoopI2::Next(VectorI2 & idx) const
{
	VectorI2	min = Min();
	VectorI2	max = Max();

	if (idx.X >= max.X)
	{
		idx.X = min.X;
		idx.Y++;
	}
	else
	{
		idx.X++;
	}
}
void LoopI2::Prev(VectorI2 & idx) const
{
	idx.X--;
	if (idx.X < Range.Min.X)
	{
		idx.X = Range.Max.X;
		idx.Y--;
	}
}
