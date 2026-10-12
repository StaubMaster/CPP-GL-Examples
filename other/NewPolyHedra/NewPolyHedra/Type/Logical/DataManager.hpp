#ifndef  NEW_POLYHEDRA_TYPE_LOGICAL_DATA_MANAGER_HPP
# define NEW_POLYHEDRA_TYPE_LOGICAL_DATA_MANAGER_HPP

# include "NewPolyHedra/Base/Logical/DataManager.hpp"

namespace NewPolyHedra
{

template<typename TypeData>
struct TypeLogicalData;

template<typename TypeData>
struct TypeLogicalDataManager : public BaseLogicalDataManager
{
	private:
	static TypeLogicalDataManager *		Current;
	public:
	static	TypeLogicalData<TypeData> *		sNewType(Pallet * pallet);

	public:
	virtual ~TypeLogicalDataManager();
	TypeLogicalDataManager();
	TypeLogicalDataManager(const TypeLogicalDataManager & other) = delete;
	TypeLogicalDataManager & operator=(const TypeLogicalDataManager & other) = delete;

	public:
	TypeLogicalData<TypeData> *		NewType(Pallet * pallet);
	BaseLogicalData *				NewBase(Pallet * pallet) override;
};
};

#endif