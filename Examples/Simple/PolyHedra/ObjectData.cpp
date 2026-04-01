#include "PolyHedra/ObjectData.hpp"



PolyHedraObjectData::~PolyHedraObjectData()
{ }
PolyHedraObjectData::PolyHedraObjectData()
	: PolyHedra(nullptr)
	, Trans()
	, Remove(false)
	, Draw(true)
{ }
PolyHedraObjectData::PolyHedraObjectData(const PolyHedraObjectData & other)
	: PolyHedra(other.PolyHedra)
	, Trans(other.Trans)
	, Remove(other.Remove)
	, Draw(other.Draw)
{ }
PolyHedraObjectData & PolyHedraObjectData::operator=(const PolyHedraObjectData & other)
{
	PolyHedra = other.PolyHedra;
	Trans = other.Trans;
	Remove = other.Remove;
	Draw = other.Draw;
	return *this;
}



PolyHedraObjectData::PolyHedraObjectData(::PolyHedra * polyhedra)
	: PolyHedra(polyhedra)
	, Trans()
	, Remove(false)
	, Draw(true)
{ }
PolyHedraObjectData::PolyHedraObjectData(::PolyHedra * polyhedra, Trans3D trans)
	: PolyHedra(polyhedra)
	, Trans(trans)
	, Remove(false)
	, Draw(true)
{ }
