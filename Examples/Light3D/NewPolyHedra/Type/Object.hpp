#ifndef  NEW_POLYHEDRA_TYPE_OBJECT_HPP
# define NEW_POLYHEDRA_TYPE_OBJECT_HPP

struct NewPolyHedra_Pallet;

# include "ObjectData.hpp"
# include "../PalletObjectData.hpp"
# include "NewPalletObjectData.hpp"

template<
	typename TypeData
>
struct NewPolyHedra_Type_Object
{
	NewPolyHedra_PalletObjectData *		PalletObjectData;
	TypeData &	Data()
	{
		return (((NewPolyHedra_Type_ObjectData<TypeData> *)(PalletObjectData -> ObjectData)) -> Data);
	}

	//~NewPolyHedra_Type_Object()
	//NewPolyHedra_Type_Object()

	void	Create(NewPolyHedra_Pallet * pallet)
	{
		if (PalletObjectData != nullptr) { return; }
		PalletObjectData = NewPalletObjectData<TypeData>(pallet);
	}
	void	Delete()
	{
		delete PalletObjectData = nullptr;
		PalletObjectData = nullptr;
	}
};

#endif