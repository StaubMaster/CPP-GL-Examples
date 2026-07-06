#ifndef  NEW_POLYHEDRA_TYPE_NEW_PALLET_OBJECT_DATA_HPP
# define NEW_POLYHEDRA_TYPE_NEW_PALLET_OBJECT_DATA_HPP

struct NewPolyHedra_Pallet;
struct NewPolyHedra_PalletObjectData;

template<
	typename TypeData
>
struct NewPolyHedra_Type_PalletObjectData;

template<
	typename TypeData
>
NewPolyHedra_Type_PalletObjectData<TypeData> * sNewPalletObjectData(NewPolyHedra_Pallet * pallet);

#endif