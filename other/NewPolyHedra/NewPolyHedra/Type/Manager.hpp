#ifndef  NEW_POLYHEDRA_TYPE_MANAGER_HPP
# define NEW_POLYHEDRA_TYPE_MANAGER_HPP

# include "NewPolyHedra/Base/Manager.hpp"

# include "NewPolyHedra/Type/Logical/ObjectManager.hpp"
# include "NewPolyHedra/Type/Display/ObjectManager.hpp"

namespace NewPolyHedra
{
template<typename LogicalData> struct DataManager : public BaseManager
{
	public:
	static DataManager *	Current;

	public:
	TypeLogicalObjectManager<LogicalData>		LogicalType;
	public:
			BaseLogicalObjectManager &		LogicalBase()		override;
	const	BaseLogicalObjectManager &		LogicalBase() const	override;

	public:
	virtual ~DataManager();
	DataManager();
	DataManager(const DataManager & other) = delete;
	DataManager & operator=(const DataManager & other) = delete;
};



template<typename LogicalData, typename DisplayData> struct TypeManager : public DataManager<LogicalData>
{
	public:
	TypeDisplayObjectManager<LogicalData, DisplayData>	DisplayType;
	public:
			BaseDisplayObjectManager &		DisplayBase()		override;
	const	BaseDisplayObjectManager &		DisplayBase() const	override;

	public:
	~TypeManager() = default;
	TypeManager() = default;
	TypeManager(const TypeManager & other) = delete;
	TypeManager & operator=(const TypeManager & other) = delete;
};
};

#endif