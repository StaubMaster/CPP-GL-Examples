#ifndef  UI_POLYHEDRA_OBJECT_DATA_HPP
# define UI_POLYHEDRA_OBJECT_DATA_HPP

# include "ValueType/Trans3D.hpp"
# include "ValueType/ColorF4.hpp"

class PolyHedraUIPalletManager;
struct PolyHedraUIData;

struct PolyHedraUIObjectData
{
	bool	Remove; // allways needed
	bool	DrawFull; // at least Draw allways needed
	bool	DrawWire;

	PolyHedraUIPalletManager *	PalletManager;

	Trans3D		Trans;
	float		Scale;
	ColorF4		Color;

	~PolyHedraUIObjectData();
	PolyHedraUIObjectData() = delete;
	PolyHedraUIObjectData(const PolyHedraUIObjectData & other) = delete;
	PolyHedraUIObjectData & operator=(const PolyHedraUIObjectData & other);

	PolyHedraUIObjectData(::PolyHedraUIPalletManager * manager);

	PolyHedraUIData		ToData() const;
};

#endif