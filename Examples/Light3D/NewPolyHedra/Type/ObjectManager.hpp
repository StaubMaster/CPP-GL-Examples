#ifndef  NEW_POLYHEDRA_TYPE_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_TYPE_OBJECT_MANAGER_HPP

# include "ObjectManager.hpp"

/*template<
	typename TypeData,
	typename TypeInstanceData
>
struct NewPolyHedra_Type_PalletObjectManager;*/

# include "PalletObjectManager.hpp"

template<
	typename TypeShaderLayout,
	typename TypeBufferLayout,
	typename TypeData,
	typename TypeInstanceData
>
struct NewPolyHedra_Type_ObjectManager : public NewPolyHedra_ObjectManager
{
	TypeShaderLayout	ShaderLayout; // Full and Wire
	TypeBufferLayout	BufferLayout; // Full and Wire

	NewPolyHedra_Type_PalletObjectManager<TypeData, TypeInstanceData> *	FindPalletObjectManager(NewPolyHedra_Pallet * pallet) const
	{
		if (pallet == nullptr) { return nullptr; }
		for (unsigned int i = 0; i < Managers.Count(); i++)
		{
			NewPolyHedra_Type_PalletObjectManager<TypeData, TypeInstanceData> * manager = (NewPolyHedra_Type_PalletObjectManager<TypeData, TypeInstanceData> *)Managers[i];
			if (manager == nullptr) { continue; }
			if (manager -> Pallet == pallet)
			{
				return manager;
			}
		}
		return nullptr;
	}
	NewPolyHedra_Type_PalletObjectManager<TypeData, TypeInstanceData> *	MakePalletObjectManager(NewPolyHedra_Pallet * pallet)
	{
		if (pallet == nullptr) { return nullptr; }
		NewPolyHedra_Type_PalletObjectManager<TypeData, TypeInstanceData> * manager = new NewPolyHedra_Type_PalletObjectManager<TypeData, TypeInstanceData>();
		manager -> Pallet = pallet;
		Managers.Insert(manager);
		return manager;
	}
	NewPolyHedra_Type_PalletObjectManager<TypeData, TypeInstanceData> *	FindMakePalletObjectManager(NewPolyHedra_Pallet * pallet)
	{
		if (pallet == nullptr) { return nullptr; }
		NewPolyHedra_Type_PalletObjectManager<TypeData, TypeInstanceData> * manager = FindPalletObjectManager(pallet);
		if (manager == nullptr)
		{
			manager = MakePalletObjectManager(pallet);
		}
		return manager;
	}
};

#endif