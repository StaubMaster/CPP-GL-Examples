#ifndef  NEW_POLYHEDRA_MANAGER_HPP
# define NEW_POLYHEDRA_MANAGER_HPP

# include "Miscellaneous/Container/Binary.hpp"

struct NewPolyHedra_PalletManager;
struct NewPolyHedra_ObjectManager;

struct NewPolyHedra_Manager
{
	NewPolyHedra_PalletManager *	PalletManager;

	Container::Binary<NewPolyHedra_ObjectManager*>	ObjectManagers;

	void	UpdatePalletObjectDatas();

	void	InstancesClear();
	void	InstancesMake();

	void	GraphicsCreate();
	void	GraphicsDelete();
	void	GraphicsDrawFull();
	void	GraphicsDrawWire();
};

#endif