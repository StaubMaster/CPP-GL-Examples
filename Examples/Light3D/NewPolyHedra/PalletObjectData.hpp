#ifndef  NEW_POLYHEDRA_PALLET_OBJECT_DATA_HPP
# define NEW_POLYHEDRA_PALLET_OBJECT_DATA_HPP

// (ObjectData) and (Pallet*)
// Should ObjectData also be a Pointer ?
// or should ObjectData be a base Pointer ?

struct NewPolyHedra_PalletObjectManager;
struct NewPolyHedra_ObjectData;

struct NewPolyHedra_PalletObjectData
{
	NewPolyHedra_PalletObjectManager *	Manager;
	NewPolyHedra_ObjectData *			Data;

	void	InstancePut() const;
};

#endif