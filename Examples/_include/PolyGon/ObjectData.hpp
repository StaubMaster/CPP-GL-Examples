#ifndef  POLYGON_OBJECT_DATA_HPP
# define POLYGON_OBJECT_DATA_HPP

# include "ValueType/Trans2D.hpp"

class PolyGon;

struct PolyGonObjectData
{
	::PolyGon *	PolyGon;
	Trans2D		Trans;

	bool	Remove;
	bool	DrawFull;
	bool	DrawWire;

	~PolyGonObjectData();
	PolyGonObjectData();
	PolyGonObjectData(const PolyGonObjectData & other);
	PolyGonObjectData & operator=(const PolyGonObjectData & other);

	PolyGonObjectData(::PolyGon * PolyGon);
	PolyGonObjectData(::PolyGon * PolyGon, Trans2D trans);
};

#endif