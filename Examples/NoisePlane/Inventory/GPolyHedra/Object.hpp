#ifndef  POLYHEDRA_OBJECT_HPP
# define POLYHEDRA_OBJECT_HPP

# include "ValueType/Trans3D.hpp"

class PolyHedra;
struct PolyHedraObjectData;

struct PolyHedraObject
{
	private:
	PolyHedraObjectData *	Data;
	public:

	bool			Is() const;
	::PolyHedra *	PolyHedra() const;

	const Trans3D &	Trans() const;
	Trans3D &		Trans();

	bool	FullVisibility() const;
	bool	WireVisibility() const;

	void	HideFull();
	void	HideWire();
	
	void	ShowFull();
	void	ShowWire();

	~PolyHedraObject();
	PolyHedraObject();
	PolyHedraObject(const PolyHedraObject & other);
	PolyHedraObject & operator=(const PolyHedraObject & other);

	PolyHedraObject(unsigned int polyhedra);
	PolyHedraObject(unsigned int polyhedra, Trans3D trans);

	PolyHedraObject(::PolyHedra * polyhedra);
	PolyHedraObject(::PolyHedra * polyhedra, Trans3D trans);

	void	Delete();
	void	Create(unsigned int polyhedra);
	void	Create(::PolyHedra * polyhedra);
};

#endif