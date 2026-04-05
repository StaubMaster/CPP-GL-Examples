#ifndef  POLYGON_OBJECT_HPP
# define POLYGON_OBJECT_HPP

# include "ValueType/Trans2D.hpp"

class PolyGon;
struct PolyGonObjectData;

struct PolyGonObject
{
	PolyGonObjectData *	Data;

	bool			Is() const;
	::PolyGon *		PolyGon() const;

	const Trans2D &	Trans() const;
	Trans2D &		Trans();

	bool	IsFullVisible() const;
	bool	IsWireVisible() const;

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
	PolyGonObject(unsigned int PolyGon, Point2D pos, Angle ang);
	PolyGonObject(unsigned int PolyGon, Point2D pos);

	PolyGonObject(::PolyGon * PolyGon);
	PolyGonObject(::PolyGon * PolyGon, Trans2D trans);
	PolyGonObject(::PolyGon * PolyGon, Point2D pos, Angle ang);
	PolyGonObject(::PolyGon * PolyGon, Point2D pos);

	void	Delete();
	void	Create(unsigned int PolyGon);
	void	Create(::PolyGon * PolyGon);
};

#endif