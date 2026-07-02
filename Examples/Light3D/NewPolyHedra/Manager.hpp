#ifndef  NEW_POLYHEDRA_MANAGER_HPP
# define NEW_POLYHEDRA_MANAGER_HPP

# include "Miscellaneous/Container/Binary.hpp"

class PolyHedra;

struct NewPolyHedra_Pallet;
struct NewPolyHedra_ObjectManager;

struct NewPolyHedra_Manager
{
	Container::Binary<NewPolyHedra_Pallet*>		Pallets;

	NewPolyHedra_Pallet *	FindPallet(PolyHedra * polyhedra) const;
	NewPolyHedra_Pallet *	MakePallet(PolyHedra * polyhedra);
	NewPolyHedra_Pallet *	FindMakePallet(PolyHedra * polyhedra);



	Container::Binary<NewPolyHedra_ObjectManager*>	ObjectManagers;

	void	InstancesClear();
	void	InstancesMake();

	void	Draw();

	void	GraphicsCreate();
	void	GraphicsDelete();
};

#endif