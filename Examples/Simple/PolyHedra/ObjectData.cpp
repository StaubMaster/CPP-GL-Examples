#include "PolyHedra/ObjectData.hpp"



PolyHedraObjectData::~PolyHedraObjectData()
{ }
PolyHedraObjectData::PolyHedraObjectData()
	: PolyHedra(nullptr)
	, Data()
{ }
PolyHedraObjectData::PolyHedraObjectData(const PolyHedraObjectData & other)
	: PolyHedra(other.PolyHedra)
	, Data(other.Data)
{ }
PolyHedraObjectData & PolyHedraObjectData::operator=(const PolyHedraObjectData & other)
{
	PolyHedra = other.PolyHedra;
	Data = other.Data;
	return *this;
}



PolyHedraObjectData::PolyHedraObjectData(::PolyHedra * polyhedra)
	: PolyHedra(polyhedra)
	, Data()
{ }
PolyHedraObjectData::PolyHedraObjectData(::PolyHedra * polyhedra, Trans3D data)
	: PolyHedra(polyhedra)
	, Data(data)
{ }
