#ifndef  NEW_POLYHEDRA_TYPE_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_TYPE_OBJECT_MANAGER_HPP

# include "../ObjectManager.hpp"
# include "PalletObjectData.hpp"
# include "PalletObjectManager.hpp"

template<
	typename TypeData
>
struct NewPolyHedra_Type_Data_ObjectManager : public NewPolyHedra_ObjectManager
{
	static NewPolyHedra_Type_Data_ObjectManager *	Current;

	~NewPolyHedra_Type_Data_ObjectManager()
	{
		Current = nullptr;
	}
	NewPolyHedra_Type_Data_ObjectManager()
	{
		Current = this;
	}
};

template<
	typename TypeData
>
NewPolyHedra_Type_Data_ObjectManager<TypeData> * NewPolyHedra_Type_Data_ObjectManager<TypeData>::Current = nullptr;



template<
	typename TypeData,
	typename TypeInstanceData
>
struct NewPolyHedra_Type_ObjectManager : public NewPolyHedra_Type_Data_ObjectManager<TypeData>
{
	NewPolyHedra_PalletObjectManager *	NewPalletObjectManager() override
	{
		return new NewPolyHedra_Type_PalletObjectManager<TypeData, TypeInstanceData>();
	}
	NewPolyHedra_PalletObjectData *	NewPalletObjectData() override
	{
		return new NewPolyHedra_Type_PalletObjectData<TypeData>();
	}
};

#endif