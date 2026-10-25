#ifndef  NEW_POLYHEDRA_TYPE_MANAGER_HPP
# define NEW_POLYHEDRA_TYPE_MANAGER_HPP

# include "NewPolyHedra/Base/Manager.hpp"

# include "NewPolyHedra/Type/Logical/ObjectManager.hpp"
# include "NewPolyHedra/Type/Display/ObjectManager.hpp"

namespace NewPolyHedra
{
//template<typename LogicalData> struct TypeLogicalObject;
//template<typename LogicalData> struct TypeLogicalObjectManager;
//template<typename LogicalData> struct DataDisplayObject;
//template<typename LogicalData> struct DataDisplayObjectManager;
template<typename LogicalData> struct DataManager : public BaseManager
{
	public:
	static DataManager *	Current;

	private:
	TypeLogicalObjectManager<LogicalData>		_LogicalManager;
	public:
			TypeLogicalObjectManager<LogicalData> &		LogicalManager()					override;
	const	TypeLogicalObjectManager<LogicalData> &		LogicalManager() const				override;

	public:
	virtual			DataDisplayObjectManager<LogicalData> &		DisplayManager()							= 0;
	virtual const	DataDisplayObjectManager<LogicalData> &		DisplayManager() const						= 0;
	virtual			DataDisplayObject<LogicalData> *			FindDisplayObject(const Pallet & pallet)	= 0;
	virtual			DataDisplayObject<LogicalData> &			TakeDisplayObject(      Pallet & pallet)	= 0;

	public:
	virtual ~DataManager();
	DataManager();
	DataManager(const DataManager & other) = delete;
	DataManager & operator=(const DataManager & other) = delete;
};



//template<typename LogicalData, typename DisplayData> struct TypeDisplayObject;
//template<typename LogicalData, typename DisplayData> struct TypeDisplayObjectManager;
template<typename LogicalData, typename DisplayData> struct TypeManager : public DataManager<LogicalData>
{
	private:
	TypeDisplayObjectManager<LogicalData, DisplayData>		_DisplayManager;
	public:
			TypeDisplayObjectManager<LogicalData, DisplayData> &	DisplayManager()							override;
	const	TypeDisplayObjectManager<LogicalData, DisplayData> &	DisplayManager() const						override;
			TypeDisplayObject<LogicalData, DisplayData> *			FindDisplayObject(const Pallet & pallet)	override;
			TypeDisplayObject<LogicalData, DisplayData> &			TakeDisplayObject(      Pallet & pallet)	override;

	public:
	~TypeManager() = default;
	TypeManager() = default;
	TypeManager(const TypeManager & other) = delete;
	TypeManager & operator=(const TypeManager & other) = delete;
};
};

#endif