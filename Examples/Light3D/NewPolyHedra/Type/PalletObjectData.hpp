#ifndef  NEW_POLYHEDRA_TYPE_PALLET_OBJECT_DATA_HPP
# define NEW_POLYHEDRA_TYPE_PALLET_OBJECT_DATA_HPP

# include "../PalletObjectData.hpp"
# include "ObjectData.hpp"

template<
	typename TypeData
>
struct NewPolyHedra_Type_PalletObjectData : public NewPolyHedra_PalletObjectData
{
	TypeData &	Data()
	{
		return ((NewPolyHedra_Type_ObjectData<TypeData> *)ObjectData) -> Data;
	}
	const TypeData &	Data() const
	{
		return ((const NewPolyHedra_Type_ObjectData<TypeData> *)ObjectData) -> Data;
	}

	NewPolyHedra_Type_PalletObjectData()
	{
		ObjectData = new NewPolyHedra_Type_ObjectData<TypeData>();
	}
};

#endif