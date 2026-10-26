#ifndef  NEW_POLYHEDRA_TYPE_DISPLAY_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_TYPE_DISPLAY_OBJECT_MANAGER_HPP

# include "NewPolyHedra/Base/Display/ObjectManager.hpp"
# include "NewPolyHedra/Type/Display/Object.hpp"

namespace NewPolyHedra
{

template<typename LogicalData> struct DataDisplayObject;
template<typename LogicalData> struct DataDisplayObjectManager : public BaseDisplayObjectManager
{
	private:
	static DataDisplayObjectManager *		Current;
	public:
	static DataDisplayObject<LogicalData> *		sFind(Pallet & pallet);
	static DataDisplayObject<LogicalData> *		sTake(Pallet & pallet);

	public:
	virtual ~DataDisplayObjectManager();
	DataDisplayObjectManager();
	DataDisplayObjectManager(const DataDisplayObjectManager & other) = delete;
	DataDisplayObjectManager & operator=(const DataDisplayObjectManager & other) = delete;



	public:		virtual unsigned int	Count() const = 0;

	public:		virtual DataDisplayObject<LogicalData> *	Find(const Pallet & pallet) const = 0;
	private:	virtual DataDisplayObject<LogicalData> &	Make(      Pallet & pallet) = 0;
	public:		virtual DataDisplayObject<LogicalData> &	Take(      Pallet & pallet) = 0;

//	public:		virtual DataDisplayObject<LogicalData> *	Find(const Pallet * pallet) const = 0;
//	private:	virtual DataDisplayObject<LogicalData> *	Make(      Pallet * pallet) = 0;
//	public:		virtual DataDisplayObject<LogicalData> *	Take(      Pallet * pallet) = 0;

};

template<typename LogicalData, typename DisplayData> struct TypeDisplayObject;
template<typename LogicalData, typename DisplayData> struct TypeDisplayObjectManager : public DataDisplayObjectManager<LogicalData>
{
	public:
	~TypeDisplayObjectManager();
	TypeDisplayObjectManager() = default;
	TypeDisplayObjectManager(const TypeDisplayObjectManager & other) = delete;
	TypeDisplayObjectManager & operator=(const TypeDisplayObjectManager & other) = delete;



	private: public:	Container::Binary<TypeDisplayObject<LogicalData, DisplayData> *>	Objects;

	public:		virtual unsigned int	Count() const override;

	public:		TypeDisplayObject<LogicalData, DisplayData> *	Find(const Pallet & pallet) const override;
	private:	TypeDisplayObject<LogicalData, DisplayData> &	Make(      Pallet & pallet) override;
	public:		TypeDisplayObject<LogicalData, DisplayData> &	Take(      Pallet & pallet) override;

//	public:		TypeDisplayObject<LogicalData, DisplayData> *	Find(const Pallet * pallet) const override;
//	private:	TypeDisplayObject<LogicalData, DisplayData> *	Make(      Pallet * pallet) override;
//	public:		TypeDisplayObject<LogicalData, DisplayData> *	Take(      Pallet * pallet) override;



	public:
	unsigned int	InstancesFullCount() const override;
	unsigned int	InstancesWireCount() const override;
	void			InstancesClear() override;

	public:
	void	GraphicsCreate() override;
	void	GraphicsDelete() override;
	void	GraphicsDrawFull() override;
	void	GraphicsDrawWire() override;
};
};

#endif