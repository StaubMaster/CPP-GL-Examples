#ifndef  NEW_POLYHEDRA_TYPE_PALLET_OBJECT_DATA_HPP
# define NEW_POLYHEDRA_TYPE_PALLET_OBJECT_DATA_HPP

# include "../PalletObjectData.hpp"

template<
	typename TypeData
>
struct NewPolyHedra_Type_PalletObjectData : public NewPolyHedra_PalletObjectData
{
	public:
	TypeData	Data;

	protected:
	const void *	DataVoid() const
	{
		return &Data;
	}
};

#endif