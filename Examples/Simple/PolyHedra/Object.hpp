#ifndef  POLYHEDRA_OBJECT_HPP
# define POLYHEDRA_OBJECT_HPP

# include "ValueType/Trans3D.hpp"

class PolyHedra;
struct PolyHedraObjectData;

struct PolyHedraObject
{
	PolyHedraObjectData * Data;

	bool			Is() const;
	const Trans3D &	Trans() const;
	Trans3D &		Trans();

	~PolyHedraObject();
	PolyHedraObject();
	PolyHedraObject(const PolyHedraObject & other);
	PolyHedraObject & operator=(const PolyHedraObject & other);

	PolyHedraObject(unsigned int polyhedra);
	PolyHedraObject(unsigned int polyhedra, Trans3D trans);
	PolyHedraObject(unsigned int polyhedra, Point3D pos, EulerAngle3D ang);
	PolyHedraObject(unsigned int polyhedra, Point3D pos);

	PolyHedraObject(::PolyHedra * polyhedra);
	PolyHedraObject(::PolyHedra * polyhedra, Trans3D trans);
	PolyHedraObject(::PolyHedra * polyhedra, Point3D pos, EulerAngle3D ang);
	PolyHedraObject(::PolyHedra * polyhedra, Point3D pos);

	void	Delete();
	void	Create(unsigned int polyhedra);
	void	Create(::PolyHedra * polyhedra);
};

#endif