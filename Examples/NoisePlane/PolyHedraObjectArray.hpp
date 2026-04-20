#ifndef  POLYHEDRA_OBJECT_ARRAY
# define POLYHEDRA_OBJECT_ARRAY

# include "PolyHedra/Object.hpp"

// put into Engine
struct PolyHedraObjectArray
{
	unsigned int		Count;
	PolyHedraObject *	Array;

	PolyHedraObject &	operator[](unsigned int i);

	~PolyHedraObjectArray();
	PolyHedraObjectArray();
	PolyHedraObjectArray(const PolyHedraObjectArray & other) = delete;
	PolyHedraObjectArray & operator=(const PolyHedraObjectArray & other) = delete;

	void Create(PolyHedra * polyhedra, unsigned int count);
	void Create(unsigned int polyhedra, unsigned int count);

	void Delete();
};

#endif