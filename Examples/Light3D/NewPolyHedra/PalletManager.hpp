#ifndef  NEW_POLYHEDRA_PALLET_MANAGER_HPP
# define NEW_POLYHEDRA_PALLET_MANAGER_HPP

# include "Generics/Container/Binary.hpp"
# include "Graphics/Attribute/General/Layout.hpp"

class PolyHedra;

namespace NewPolyHedra
{
struct Pallet;

struct PalletManager
{
	static PalletManager *		Current;

	~PalletManager();
	PalletManager();
	PalletManager(const PalletManager & other) = delete;
	PalletManager & operator=(const PalletManager & other) = delete;



	Container::Binary<Pallet*>		Pallets;

	Pallet *	FindPallet(PolyHedra * polyhedra) const;
	Pallet *	MakePallet(PolyHedra * polyhedra);
	Pallet *	FindMakePallet(PolyHedra * polyhedra);



	::Attribute::Layout *	BufferFullLayout;
	::Attribute::Layout *	BufferWireLayout;

	void	GraphicsCreate();
	void	GraphicsDelete();
};
};

#endif