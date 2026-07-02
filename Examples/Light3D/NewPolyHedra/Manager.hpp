#ifndef  NEW_POLYHEDRA_MANAGER_HPP
# define NEW_POLYHEDRA_MANAGER_HPP

# include "Miscellaneous/Container/Binary.hpp"

struct NewPolyHedra_Pallet;
struct NewPolyHedra_ObjectManager;

struct NewPolyHedra_Manager
{
	Container::Binary<NewPolyHedra_Pallet*>			Pallets;
	Container::Binary<NewPolyHedra_ObjectManager*>	ObjectManagers;

	void	InstancesClear();
	void	InstancesMake();
};

#endif