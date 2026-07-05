#ifndef  NEW_POLYHEDRA_PALLET_OBJECT_DATA_HPP
# define NEW_POLYHEDRA_PALLET_OBJECT_DATA_HPP

// (ObjectData) and (Pallet*)
// Should ObjectData also be a Pointer ?
// or should ObjectData be a base Pointer ?

struct NewPolyHedra_PalletObjectManager;
struct NewPolyHedra_ObjectData;
struct NewPolyHedra_Pallet;

struct NewPolyHedra_PalletObjectData
{
	bool	Remove;
	bool	Display;



	NewPolyHedra_PalletObjectManager *	Manager; // (== null) means delete
	NewPolyHedra_ObjectData *			ObjectData; // why is this a pointer ?
	// because Datatype varies

	~NewPolyHedra_PalletObjectData();
	NewPolyHedra_PalletObjectData();



	void	InstancePut() const;
};

#endif