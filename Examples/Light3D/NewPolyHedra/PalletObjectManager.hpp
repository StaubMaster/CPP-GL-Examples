#ifndef  NEW_POLYHEDRA_PALLET_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_PALLET_OBJECT_MANAGER_HPP

# include "Miscellaneous/Container/Binary.hpp"

struct NewPolyHedra_Pallet;
struct NewPolyHedra_ObjectData;

struct NewPolyHedra_PalletObjectManager
{
	NewPolyHedra_Pallet *	Pallet;

	//Buffer;
	//Container::Binary<void>		InstanceData;

	// InstanceData can not be done with Poitners
	// so it needs to be specified with Template

	// template code should be minimized

	// accumulate InstanceData using BlockList
	// InstancesDone() to turn BlockList into Array

	void	InstancesClear();
	void	InstancePut(const NewPolyHedra_ObjectData & data);
	void	InstancePut(const NewPolyHedra_ObjectData * data);
};

#endif