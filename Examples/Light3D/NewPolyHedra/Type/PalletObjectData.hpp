#ifndef  NEW_POLYHEDRA_TYPE_PALLET_OBJECT_DATA_HPP
# define NEW_POLYHEDRA_TYPE_PALLET_OBJECT_DATA_HPP

# include "../PalletObjectData.hpp"

namespace NewPolyHedra
{
template<
	typename TypeData
>
struct Type_PalletObjectData : public PalletObjectData
{
	public:
	~Type_PalletObjectData() = default;
	Type_PalletObjectData() = default;
	Type_PalletObjectData(const Type_PalletObjectData & other) = delete;
	Type_PalletObjectData & operator=(const Type_PalletObjectData & other) = delete;

	public:
	TypeData	Data;

	protected:
	const void *	DataVoid() const
	{
		return &Data;
	}
};
};

#endif