#ifndef  POLYHEDRA_OBJECT_DATA_HPP
# define POLYHEDRA_OBJECT_DATA_HPP

# include "ValueType/Trans3D.hpp"

class PolyHedra;

struct PolyHedraObjectData
{
	::PolyHedra *	PolyHedra;
	Trans3D			Data;

	~PolyHedraObjectData();
	PolyHedraObjectData();
	PolyHedraObjectData(const PolyHedraObjectData & other);
	PolyHedraObjectData & operator=(const PolyHedraObjectData & other);

	PolyHedraObjectData(::PolyHedra * polyhedra);
	PolyHedraObjectData(::PolyHedra * polyhedra, Trans3D data);
};

#endif