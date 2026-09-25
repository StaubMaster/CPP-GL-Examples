#ifndef  POLYGON_OBJECT_HPP
# define POLYGON_OBJECT_HPP

# include "ValueType/Trans/2D.hpp"

class PolyGon;
struct PolyGonObjectData;

struct PolyGonObject
{
	PolyGonObjectData *	Data;

	bool			Is() const;
	::PolyGon *		PolyGon() const;

	const Trans2D &	Trans() const;
	Trans2D &		Trans();

	bool	FullVisibility() const;
	bool	WireVisibility() const;

	void	HideFull();
	void	HideWire();
	
	void	ShowFull();
	void	ShowWire();

	~PolyGonObject();
	PolyGonObject();
	PolyGonObject(const PolyGonObject & other);
	PolyGonObject & operator=(const PolyGonObject & other);

	PolyGonObject(unsigned int PolyGon);
	PolyGonObject(unsigned int PolyGon, Trans2D trans);

	PolyGonObject(::PolyGon * PolyGon);
	PolyGonObject(::PolyGon * PolyGon, Trans2D trans);

	void	Delete();
	void	Create(unsigned int PolyGon);
	void	Create(::PolyGon * PolyGon);
};

#endif