#ifndef  NEW_POLYHEDRA_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_OBJECT_MANAGER_HPP

# include "Miscellaneous/Container/Binary.hpp"
# include "Graphics/Shader/Base.hpp"

struct NewPolyHedra_Pallet;
struct NewPolyHedra_PalletObjectManager;
struct NewPolyHedra_PalletObjectData;
struct NewPolyHedra_ObjectData;

struct NewPolyHedra_ObjectManager
{
	Container::Binary<NewPolyHedra_PalletObjectManager*>	Managers;

	virtual NewPolyHedra_PalletObjectManager *	NewPalletObjectManager() = 0;

	NewPolyHedra_PalletObjectManager *	FindPalletObjectManager(NewPolyHedra_Pallet * pallet) const;
	NewPolyHedra_PalletObjectManager *	MakePalletObjectManager(NewPolyHedra_Pallet * pallet);
	NewPolyHedra_PalletObjectManager *	FindMakePalletObjectManager(NewPolyHedra_Pallet * pallet);



	Container::Binary<NewPolyHedra_PalletObjectData*>	PalletObjectDatas;

	virtual NewPolyHedra_ObjectData *	NewObjectData() = 0;

	NewPolyHedra_PalletObjectData *		NewPalletObjectData(NewPolyHedra_Pallet * pallet);

	void	UpdatePalletObjectDatas();



	::Shader::Base	Shader; // Full and Wire

	void	InstancesClear();
	void	InstancesMake();

	void	Draw();

	void	GraphicsCreate();
	void	GraphicsDelete();
};

#endif