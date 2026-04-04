#include "PolyGon/ObjectData.hpp"



PolyGonObjectData::~PolyGonObjectData()
{ }
PolyGonObjectData::PolyGonObjectData()
	: PolyGon(nullptr)
	, Trans()
	, Remove(false)
	, DrawFull(true)
	, DrawWire(false)
{ }
PolyGonObjectData::PolyGonObjectData(const PolyGonObjectData & other)
	: PolyGon(other.PolyGon)
	, Trans(other.Trans)
	, Remove(other.Remove)
	, DrawFull(other.DrawFull)
	, DrawWire(other.DrawWire)
{ }
PolyGonObjectData & PolyGonObjectData::operator=(const PolyGonObjectData & other)
{
	PolyGon = other.PolyGon;
	Trans = other.Trans;
	Remove = other.Remove;
	DrawFull = other.DrawFull;
	DrawWire = other.DrawWire;
	return *this;
}



PolyGonObjectData::PolyGonObjectData(::PolyGon * PolyGon)
	: PolyGon(PolyGon)
	, Trans()
	, Remove(false)
	, DrawFull(true)
	, DrawWire(false)
{ }
PolyGonObjectData::PolyGonObjectData(::PolyGon * PolyGon, Trans2D trans)
	: PolyGon(PolyGon)
	, Trans(trans)
	, Remove(false)
	, DrawFull(true)
	, DrawWire(false)
{ }
