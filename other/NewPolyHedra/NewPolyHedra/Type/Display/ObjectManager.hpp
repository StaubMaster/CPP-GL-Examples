#ifndef  NEW_POLYHEDRA_TYPE_DISPLAY_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_TYPE_DISPLAY_OBJECT_MANAGER_HPP

# include "NewPolyHedra/Base/Display/ObjectManager.hpp"

namespace NewPolyHedra
{
template<typename LogicalData> struct DataDisplayObjectManager : public BaseDisplayObjectManager
{
	private:
	static DataDisplayObjectManager *		Current;
	public:
	static BaseDisplayObject *	sFind(Pallet * pallet);
	static BaseDisplayObject *	sTake(Pallet * pallet);

	public:
	virtual ~DataDisplayObjectManager();
	DataDisplayObjectManager();
	DataDisplayObjectManager(const DataDisplayObjectManager & other) = delete;
	DataDisplayObjectManager & operator=(const DataDisplayObjectManager & other) = delete;
};

template<typename LogicalData, typename DisplayData> struct TypeDisplayObjectManager : public DataDisplayObjectManager<LogicalData>
{
	public:
	~TypeDisplayObjectManager() = default;
	TypeDisplayObjectManager() = default;
	TypeDisplayObjectManager(const TypeDisplayObjectManager & other) = delete;
	TypeDisplayObjectManager & operator=(const TypeDisplayObjectManager & other) = delete;

	public:
	BaseDisplayObject *		NewBase(Pallet & pallet) override;
};
};

#endif