#ifndef  NEW_POLYHEDRA_TYPE_MANAGER_HPP
# define NEW_POLYHEDRA_TYPE_MANAGER_HPP

# include "NewPolyHedra/Base/Manager.hpp"

# include "NewPolyHedra/Type/Logical/ObjectManager.hpp"
# include "NewPolyHedra/Type/Display/ObjectManager.hpp"

namespace NewPolyHedra
{
template<typename LogicalData> struct DataManager : public BaseManager
{
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
	virtual ~DataManager() = default;
	DataManager() = default;
	DataManager(const DataManager & other) = delete;
	DataManager & operator=(const DataManager & other) = delete;



	//private:
	//static DataManager *	Current_;
	//public:
	//static DataManager &	Current();
	//static bool		CheckCurrent();
	//private:
	//static void		ClearCurrent();
	//bool	IsCurrent() const;
	//void	MakeCurrent();
};



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
	~TypeManager();
	TypeManager();
	TypeManager(const TypeManager & other) = delete;
	TypeManager & operator=(const TypeManager & other) = delete;



	private:
	static TypeManager *	Current_;
	public:
	static TypeManager &	Current();
	static bool		CheckCurrent();
	private:
	static void		ClearCurrent();
	bool	IsCurrent() const;
	void	MakeCurrent();
};
};

#endif