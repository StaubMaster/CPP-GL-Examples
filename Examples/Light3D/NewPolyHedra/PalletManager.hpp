#ifndef  NEW_POLYHEDRA_PALLET_MANAGER_HPP
# define NEW_POLYHEDRA_PALLET_MANAGER_HPP

# include "Miscellaneous/Container/Binary.hpp"
# include "Graphics/Attribute/General/Layout.hpp"

class PolyHedra;

struct NewPolyHedra_Pallet;

struct NewPolyHedra_PalletManager
{
	static NewPolyHedra_PalletManager *		Current;

	~NewPolyHedra_PalletManager();
	NewPolyHedra_PalletManager();



	Container::Binary<NewPolyHedra_Pallet*>		Pallets;

	NewPolyHedra_Pallet *	FindPallet(PolyHedra * polyhedra) const;
	NewPolyHedra_Pallet *	MakePallet(PolyHedra * polyhedra);
	NewPolyHedra_Pallet *	FindMakePallet(PolyHedra * polyhedra);



	::Attribute::Layout *	BufferFullLayout;
	::Attribute::Layout *	BufferWireLayout;

	void	GraphicsCreate();
	void	GraphicsDelete();
};

#endif