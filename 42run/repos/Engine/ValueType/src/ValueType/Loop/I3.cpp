#include "ValueType/Loop/I3.hpp"



LoopI3::~LoopI3()
{ }

LoopI3::LoopI3() :
	Range()
{ }
LoopI3::LoopI3(VectorI3 min, VectorI3 max) :
	Range(min, max),
	MinExclude(false),
	MaxExclude(true)
{ }
LoopI3::LoopI3(VectorI3 min, Bool3 minEx, VectorI3 max, Bool3 maxEx) :
	Range(min, max),
	MinExclude(minEx),
	MaxExclude(maxEx)
{ }

LoopI3::LoopI3(const LoopI3 & other) :
	Range(other.Range)
{ }
LoopI3 & LoopI3::operator=(const LoopI3 & other)
{
	Range = other.Range;
	return *this;
}



VectorI3 LoopI3::Min() const
{
	VectorI3 idx(Range.Min);
	if (MinExclude.GetX()) { idx.X++; }
	if (MinExclude.GetY()) { idx.Y++; }
	if (MinExclude.GetZ()) { idx.Z++; }
	return idx;
}
VectorI3 LoopI3::Max() const
{
	VectorI3 idx(Range.Max);
	if (MaxExclude.GetX()) { idx.X--; }
	if (MaxExclude.GetY()) { idx.Y--; }
	if (MaxExclude.GetZ()) { idx.Z--; }
	return idx;
}
VectorI3 LoopI3::Size() const
{
	return (Min() - Max());
}



Bool3 LoopI3::Check(VectorI3 idx) const
{
	Bool3 min;
	if (MinExclude.GetX()) { min.SetX(idx.X > Range.Min.X); } else { min.SetX(idx.X >= Range.Min.X); }
	if (MinExclude.GetY()) { min.SetY(idx.Y > Range.Min.Y); } else { min.SetY(idx.Y >= Range.Min.Y); }
	if (MinExclude.GetZ()) { min.SetZ(idx.Z > Range.Min.Z); } else { min.SetZ(idx.Z >= Range.Min.Z); }

	Bool3 max;
	if (MaxExclude.GetX()) { max.SetX(idx.X < Range.Max.X); } else { max.SetX(idx.X <= Range.Max.X); }
	if (MaxExclude.GetY()) { max.SetY(idx.Y < Range.Max.Y); } else { max.SetY(idx.Y <= Range.Max.Y); }
	if (MaxExclude.GetZ()) { max.SetZ(idx.Z < Range.Max.Z); } else { max.SetZ(idx.Z <= Range.Max.Z); }

	return min & max;
}



/*	Problem
Overflow might happen
check before ++ and --
*/
void LoopI3::Next(VectorI3 & idx) const
{
	VectorI3	min = Min();
	VectorI3	max = Max();

	if (idx.X >= max.X)
	{
		idx.X = min.X;
		if (idx.Y >= max.Y)
		{
			idx.Y = min.Y;
			idx.Z++;
		}
		else
		{
			idx.Y++;
		}
	}
	else
	{
		idx.X++;
	}
}
void LoopI3::Prev(VectorI3 & idx) const
{
	idx.X--;
	if (idx.X < Range.Min.X)
	{
		idx.X = Range.Max.X;
		idx.Y--;
		if (idx.Y < Range.Min.Y)
		{
			idx.Y = Range.Max.Y;
			idx.Z--;
		}
	}
}
