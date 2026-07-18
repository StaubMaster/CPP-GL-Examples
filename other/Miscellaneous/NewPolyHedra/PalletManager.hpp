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
	public:
	static PalletManager *		Current;

	public:
	~PalletManager();
	PalletManager();
	PalletManager(const PalletManager & other) = delete;
	PalletManager & operator=(const PalletManager & other) = delete;



	private:
	public:
	Container::Binary<Pallet*>		Pallets;

	public:
	Pallet *	FindPallet(PolyHedra * polyhedra) const;
	private:
	Pallet *	MakePallet(PolyHedra * polyhedra);
	public:
	Pallet *	FindMakePallet(PolyHedra * polyhedra);

	// Find Name



	public:
	::Attribute::Layout *	BufferFullLayout;
	::Attribute::Layout *	BufferWireLayout;

	public:
	void	GraphicsCreate();
	void	GraphicsDelete();
};
};

#endif