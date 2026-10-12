#ifndef  NEW_POLYHEDRA_PALLET_MANAGER_HPP
# define NEW_POLYHEDRA_PALLET_MANAGER_HPP

# include "Generics/Container/Binary.hpp"
# include "Graphics/Attribute/General/Layout.hpp"

#include "NewPolyHedra/Pallet/Full/Layout.hpp"
#include "NewPolyHedra/Pallet/Wire/Layout.hpp"

class PolyHedra;

namespace NewPolyHedra
{
struct Pallet;
struct PalletManager
{
	private:
	static PalletManager *		Current;
	public:
	static Pallet *		sFind(PolyHedra * polyhedra);
	static Pallet *		sTake(PolyHedra * polyhedra);

	public:
	~PalletManager();
	PalletManager();
	PalletManager(const PalletManager & other) = delete;
	PalletManager & operator=(const PalletManager & other) = delete;



	private:
	Container::Binary<Pallet*>		Pallets;

	public:		Pallet *	Find(PolyHedra * polyhedra) const;
	private:	Pallet *	Make(PolyHedra * polyhedra);
	public:		Pallet *	Take(PolyHedra * polyhedra);

	// Find Name



	// seperate into PalletGraphics / GraphicsMain

	public:
	PalletFull::Layout		BufferFullLayout;
	PalletWire::Layout		BufferWireLayout;

	public:
	void	GraphicsCreate();
	void	GraphicsDelete();
};
};

#endif