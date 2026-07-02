#ifndef  NEW_POLYHEDRA_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_OBJECT_MANAGER_HPP

# include "Miscellaneous/Container/Binary.hpp"
# include "Graphics/Shader/Base.hpp"

struct NewPolyHedra_PalletObjectManager;
struct NewPolyHedra_PalletObjectData;

struct NewPolyHedra_Pallet;

struct NewPolyHedra_ObjectManager
{
	Container::Binary<NewPolyHedra_PalletObjectManager*>	Managers;

	//NewPolyHedra_PalletObjectManager *	FindPalletObjectManager(NewPolyHedra_Pallet * pallet) const;
	//NewPolyHedra_PalletObjectManager *	MakePalletObjectManager(NewPolyHedra_Pallet * pallet);
	//NewPolyHedra_PalletObjectManager *	FindMakePalletObjectManager(NewPolyHedra_Pallet * pallet);



	Container::Binary<NewPolyHedra_PalletObjectData*>		Objects;

	::Shader::Base	Shader; // Full and Wire

	void	InstancesClear();
	void	InstancesMake();

	void	Draw();

	void	GraphicsCreate();
	void	GraphicsDelete();
};

#endif