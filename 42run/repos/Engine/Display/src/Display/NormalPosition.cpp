#include "Display/NormalPosition.hpp"



NormalPosition::~NormalPosition()
{ }
NormalPosition::NormalPosition()
	: Rel(-1, +1)
	, Abs(0, 1)
{ }

NormalPosition::NormalPosition(const NormalPosition & other)
	: Rel(other.Rel)
	, Abs(other.Abs)
{ }
NormalPosition & NormalPosition::operator=(const NormalPosition & other)
{
	Rel = other.Rel;
	Abs = other.Abs;
	return *this;
}



VectorF2 NormalPosition::RelToAbs(VectorF2 pos) { return (pos + 1) / 2; }
VectorF2 NormalPosition::AbsToRel(VectorF2 pos) { return (pos * 2) - 1; }



NormalPosition NormalPosition::FromRel(VectorF2 pos)
{
	NormalPosition normal_pos;
	normal_pos.Rel = pos;
	normal_pos.Abs = RelToAbs(pos);
	return normal_pos;
}
NormalPosition NormalPosition::FromAbs(VectorF2 pos)
{
	NormalPosition normal_pos;
	normal_pos.Rel = AbsToRel(pos);
	normal_pos.Abs = pos;
	return normal_pos;
}
