#ifndef  NEW_POLYHEDRA_TYPE_LOGICAL_DATA_HPP
# define NEW_POLYHEDRA_TYPE_LOGICAL_DATA_HPP

# include "NewPolyHedra/Base/Logical/Data.hpp"

class PolyHedra;

namespace NewPolyHedra
{
struct Pallet;

template<typename TypeData> struct TypeLogicalData : public BaseLogicalData
{
	public:
	~TypeLogicalData() = default;
	TypeLogicalData() = default;
	TypeLogicalData(const TypeLogicalData & other) = delete;
	TypeLogicalData & operator=(const TypeLogicalData & other) = delete;

	public:
	TypeData	Data;

	protected:
	const void *	DataVoid() const;

	public:
	static TypeLogicalData<TypeData> *	New(Pallet * pallet);
	//static TypeLogicalData<TypeData> *	New(PolyHedra * polyhedra);
};
};

#endif