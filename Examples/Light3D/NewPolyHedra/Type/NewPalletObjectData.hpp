#ifndef  NEW_POLYHEDRA_TYPE_NEW_PALLET_OBJECT_DATA_HPP
# define NEW_POLYHEDRA_TYPE_NEW_PALLET_OBJECT_DATA_HPP

class PolyHedra;

namespace NewPolyHedra
{
struct Pallet;
struct PalletObjectData;

template<
	typename TypeData
>
struct Type_PalletObjectData;

template<
	typename TypeData
>
Type_PalletObjectData<TypeData> * sNewPalletObjectData(Pallet * pallet);

template<
	typename TypeData
>
Type_PalletObjectData<TypeData> * sNewPalletObjectData(PolyHedra * polyhedra);
};

#endif