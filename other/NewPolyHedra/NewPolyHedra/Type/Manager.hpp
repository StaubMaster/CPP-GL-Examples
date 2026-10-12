#ifndef  NEW_POLYHEDRA_TYPE_MANAGER_HPP
# define NEW_POLYHEDRA_TYPE_MANAGER_HPP

# include "NewPolyHedra/Base/Manager.hpp"

# include "NewPolyHedra/Type/Logical/DataManager.hpp"
# include "NewPolyHedra/Type/Display/DataManager.hpp"

namespace NewPolyHedra
{
template<typename TypeData>
struct DataManager : public BaseManager
{
	public:
	static DataManager *	Current;

	public:
	TypeLogicalDataManager<TypeData>	LogicalType;
	public:
			BaseLogicalDataManager &	LogicalBase()		override;
	const	BaseLogicalDataManager &	LogicalBase() const	override;

	public:
	virtual ~DataManager();
	DataManager();
	DataManager(const DataManager & other) = delete;
	DataManager & operator=(const DataManager & other) = delete;
};



template<typename TypeData, typename TypeInstanceData>
struct TypeManager : public DataManager<TypeData>
{
	public:
	TypeDisplayDataManager<TypeData, TypeInstanceData>		DisplayType;
	public:
			BaseDisplayDataManager &	DisplayBase()		override;
	const	BaseDisplayDataManager &	DisplayBase() const	override;

	public:
	~TypeManager() = default;
	TypeManager() = default;
	TypeManager(const TypeManager & other) = delete;
	TypeManager & operator=(const TypeManager & other) = delete;
};
};

#endif