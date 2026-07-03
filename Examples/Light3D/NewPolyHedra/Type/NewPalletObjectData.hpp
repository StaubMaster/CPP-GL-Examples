#ifndef  NEW_POLYHEDRA_TYPE_NEW_PALLET_OBJECT_DATA_HPP
# define NEW_POLYHEDRA_TYPE_NEW_PALLET_OBJECT_DATA_HPP

struct NewPolyHedra_Pallet;
struct NewPolyHedra_PalletObjectData;

class PolyHedra;

template<
	typename TypeData
>
NewPolyHedra_PalletObjectData * NewPalletObjectData(NewPolyHedra_Pallet * pallet);

#endif