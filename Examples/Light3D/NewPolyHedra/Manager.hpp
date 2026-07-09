#ifndef  NEW_POLYHEDRA_MANAGER_HPP
# define NEW_POLYHEDRA_MANAGER_HPP

# include "Generics/Container/Binary.hpp"

namespace NewPolyHedra
{
struct PalletManager;
struct ObjectManager;

struct Manager
{
	~Manager() = default;
	Manager() = default;
	Manager(const Manager & other) = delete;
	Manager & operator=(const Manager & other) = delete;

	NewPolyHedra::PalletManager *	PalletManager = nullptr;

	Container::Binary<ObjectManager*>	ObjectManagers;

	void	UpdatePalletObjectDatas();

	void	InstancesClear();
	void	InstancesMake();

	void	GraphicsCreate();
	void	GraphicsDelete();
	void	GraphicsDrawFull();
	void	GraphicsDrawWire();
};
};

#endif