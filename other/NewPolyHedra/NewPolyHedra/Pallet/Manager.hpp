#ifndef  NEW_POLYHEDRA_PALLET_MANAGER_HPP
# define NEW_POLYHEDRA_PALLET_MANAGER_HPP

# include "Generics/Container/Binary.hpp"

//#include "NewPolyHedra/Pallet/Full/Layout.hpp"
//#include "NewPolyHedra/Pallet/Wire/Layout.hpp"

class PolyHedra;

namespace NewPolyHedra
{
struct Pallet;
struct PalletManager
{
	private:
	static PalletManager *		Current;
	public:
	static Pallet *		sFind(PolyHedra & polyhedra);
	static Pallet *		sTake(PolyHedra & polyhedra);

	public:
	~PalletManager();
	PalletManager();
	PalletManager(const PalletManager & other) = delete;
	PalletManager & operator=(const PalletManager & other) = delete;



	private: public:
	Container::Binary<Pallet*>		Pallets;

	// Count()
	// operator[]

	public:		Pallet *	Find(const PolyHedra & polyhedra) const;
	private:	Pallet &	Make(      PolyHedra & polyhedra);
	public:		Pallet &	Take(      PolyHedra & polyhedra);

//	public:		Pallet *	Find(const PolyHedra * polyhedra) const;
//	private:	Pallet *	Make(      PolyHedra * polyhedra);
//	public:		Pallet *	Take(      PolyHedra * polyhedra);



	// seperate into PalletGraphics / GraphicsMain

	public:
	//PalletFull::Layout		BufferFullLayout;
	//PalletWire::Layout		BufferWireLayout;

	public:
	void	GraphicsCreate();
	void	GraphicsDelete();
};
};

#endif