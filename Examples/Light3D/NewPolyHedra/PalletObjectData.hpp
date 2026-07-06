#ifndef  NEW_POLYHEDRA_PALLET_OBJECT_DATA_HPP
# define NEW_POLYHEDRA_PALLET_OBJECT_DATA_HPP

struct NewPolyHedra_PalletObjectManager;

struct NewPolyHedra_PalletObjectData
{
	bool	Remove;
	bool	DisplayFull;
	bool	DisplayWire;

	NewPolyHedra_PalletObjectManager *	Manager;

	virtual ~NewPolyHedra_PalletObjectData();
	NewPolyHedra_PalletObjectData();

	virtual const void *	DataVoid() const = 0;

	void	InstancePut() const;
};

#endif