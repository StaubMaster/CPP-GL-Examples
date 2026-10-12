#ifndef  NEW_POLYHEDRA_TYPE_DISPLAY_DATA_MANAGER_HPP
# define NEW_POLYHEDRA_TYPE_DISPLAY_DATA_MANAGER_HPP

# include "NewPolyHedra/Base/Display/DataManager.hpp"

namespace NewPolyHedra
{
template<typename TypeData>
struct DataDisplayDataManager : public BaseDisplayDataManager
{
	private:
	static DataDisplayDataManager *		Current;
	public:
	static BaseDisplayData *	sFind(Pallet * pallet);
	static BaseDisplayData *	sTake(Pallet * pallet);

	public:
	virtual ~DataDisplayDataManager();
	DataDisplayDataManager();
	DataDisplayDataManager(const DataDisplayDataManager & other) = delete;
	DataDisplayDataManager & operator=(const DataDisplayDataManager & other) = delete;
};

template<typename TypeData, typename TypeInstanceData>
struct TypeDisplayDataManager : public DataDisplayDataManager<TypeData>
{
	public:
	~TypeDisplayDataManager() = default;
	TypeDisplayDataManager() = default;
	TypeDisplayDataManager(const TypeDisplayDataManager & other) = delete;
	TypeDisplayDataManager & operator=(const TypeDisplayDataManager & other) = delete;

	public:
	BaseDisplayData *	NewBase(Pallet & pallet) override;
};
};

#endif