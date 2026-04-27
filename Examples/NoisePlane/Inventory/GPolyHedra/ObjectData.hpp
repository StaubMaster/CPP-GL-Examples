#ifndef  POLYHEDRA_OBJECT_DATA_HPP
# define POLYHEDRA_OBJECT_DATA_HPP

# include "ValueType/Trans3D.hpp"

class PolyHedra;

struct PolyHedraObjectData
{
	::PolyHedra *	PolyHedra;
	Trans3D			Trans;

	bool	Remove;
	bool	DrawFull;
	bool	DrawWire;

	~PolyHedraObjectData();
	PolyHedraObjectData();
	PolyHedraObjectData(const PolyHedraObjectData & other);
	PolyHedraObjectData & operator=(const PolyHedraObjectData & other);

	PolyHedraObjectData(::PolyHedra * polyhedra);
};

#endif