#ifndef  POLYHEDRA_OBJECT_DATA_HPP
# define POLYHEDRA_OBJECT_DATA_HPP

# include "ValueType/Trans3D.hpp"

class PolyHedra;

struct PolyHedraObjectData
{
	::PolyHedra *	PolyHedra;
	Trans3D			Trans;

	bool	Remove;	// Remove this Frame
	bool	Draw;	// Draw this Frame

	~PolyHedraObjectData();
	PolyHedraObjectData();
	PolyHedraObjectData(const PolyHedraObjectData & other);
	PolyHedraObjectData & operator=(const PolyHedraObjectData & other);

	PolyHedraObjectData(::PolyHedra * polyhedra);
	PolyHedraObjectData(::PolyHedra * polyhedra, Trans3D trans);
};

#endif