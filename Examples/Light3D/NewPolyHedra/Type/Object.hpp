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

	~NewPolyHedra_Type_Object()
	{
		PalletObjectData -> Remove = true;
		/*if (PalletObjectData != nullptr)
		{
			if (!PalletObjectData -> Remove)
			{
				PalletObjectData -> Remove = true;
			}
			else
			{
				delete PalletObjectData;
			}
		}*/
	}
	NewPolyHedra_Type_Object()
		: PalletObjectData(nullptr)
	{ }
	NewPolyHedra_Type_Object(NewPolyHedra_Pallet * pallet)
		: PalletObjectData(NewPalletObjectData<TypeData>(pallet))
	{ }

	NewPolyHedra_Type_Object(const NewPolyHedra_Type_Object & other) = delete;
	NewPolyHedra_Type_Object & operator=(const NewPolyHedra_Type_Object & other) = delete;

	void	Delete()
	{
		PalletObjectData -> Remove = true;
		PalletObjectData = nullptr;
	}
	void	Create(NewPolyHedra_Pallet * pallet)
	{
		if (PalletObjectData != nullptr) { return; }
		PalletObjectData = NewPalletObjectData<TypeData>(pallet);
	}
	// Create(PolyHedra)
};

#endif