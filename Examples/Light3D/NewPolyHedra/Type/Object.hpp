#ifndef  NEW_POLYHEDRA_TYPE_OBJECT_HPP
# define NEW_POLYHEDRA_TYPE_OBJECT_HPP

struct NewPolyHedra_Pallet;

/*template<
	typename TypeData
>
struct NewPolyHedra_Type_ObjectData;*/

# include "ObjectData.hpp"
# include "../PalletObjectData.hpp"

template<
	typename TypeData
>
struct NewPolyHedra_Type_Object
{
	//NewPolyHedra_Type_ObjectData<TypeData> *	_Data;
	//TypeData &	Data() { (_Data -> Data); }

	NewPolyHedra_PalletObjectData *	PalletObjectData;
	TypeData &	Data()
	{
		return (((NewPolyHedra_Type_ObjectData<TypeData> *)(PalletObjectData -> ObjectData)) -> Data);
	}

	/*
	these require the Managers
	but i dont want including object to include too much other stuff
	inheret from NewPolyHedra_PalletObjectData, put these there
	*/
	void	Create(NewPolyHedra_Pallet * pallet);
	void	Delete();
};

#endif