#include "Display/PixelSize.hpp"
#include "Display/PixelPosition.hpp"
#include "Display/NormalPosition.hpp"



PixelSize::~PixelSize()
{ }
PixelSize::PixelSize()
	: Full()
	, Half()
{ }

PixelSize::PixelSize(const PixelSize & other)
	: Full(other.Full)
	, Half(other.Half)
{ }
PixelSize & PixelSize::operator=(const PixelSize & other)
{
	Full = other.Full;
	Half = other.Half;
	return *this;
}



void PixelSize::ChangeFull(VectorF2 size)
{
	Full = size;
	Half = size / 2;
}

PixelSize PixelSize::FromFull(VectorF2 size)
{
	PixelSize pixel_size;
	pixel_size.ChangeFull(size);
	return pixel_size;
}



PixelPosition PixelSize::PosFromFull(VectorF2 pos) const
{
	PixelPosition pixel_pos;
	pixel_pos.Corner = pos;
	pixel_pos.Center = pos - Half;
	return pixel_pos;
}
PixelPosition PixelSize::PosFromHalf(VectorF2 pos) const
{
	PixelPosition pixel_pos;
	pixel_pos.Center = pos + Half;
	pixel_pos.Center = pos;
	return pixel_pos;
}



PixelPosition PixelSize::Convert(NormalPosition pos) const
{
	PixelPosition pixel_pos;
	pixel_pos.Corner = pos.Abs * Full;
	pixel_pos.Center = pos.Rel * Half;
	return pixel_pos;
}
NormalPosition PixelSize::Convert(PixelPosition pos) const
{
	NormalPosition normal_pos;
	normal_pos.Abs = pos.Corner / Full;
	normal_pos.Rel = pos.Center / Half;
	return normal_pos;
}



VectorF2 PixelSize::PosFullToNormalAbs(VectorF2 pos) const
{
	return pos / Full;
}
VectorF2 PixelSize::PosFullToNormalRel(VectorF2 pos) const
{
	return NormalPosition::AbsToRel(pos / Full);
}

VectorF2 PixelSize::PosNormalAbsToFull(VectorF2 pos) const
{
	return pos * Full;
}
VectorF2 PixelSize::PosNormalRelToFull(VectorF2 pos) const
{
	return NormalPosition::RelToAbs(pos) * Full;
}



VectorF2 PixelSize::SizeFullToNormalAbs(VectorF2 pos) const
{
	return pos / Full;
}
VectorF2 PixelSize::SizeFullToNormalRel(VectorF2 pos) const
{
	return (pos / Full) * 2;
}

VectorF2 PixelSize::SizeNormalAbsToFull(VectorF2 pos) const
{
	return pos * Full;
}
VectorF2 PixelSize::SizeNormalRelToFull(VectorF2 pos) const
{
	return (pos / 2) * Full;
}
