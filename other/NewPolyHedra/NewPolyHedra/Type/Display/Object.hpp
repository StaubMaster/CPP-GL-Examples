#ifndef  NEW_POLYHEDRA_TYPE_DISPLAY_OBJECT_HPP
# define NEW_POLYHEDRA_TYPE_DISPLAY_OBJECT_HPP

# include "NewPolyHedra/Base/Display/Object.hpp"

# include "Generics/Container/Binary.hpp"

namespace NewPolyHedra
{
template<typename LogicalData> struct DataDisplayObject : public BaseDisplayObject
{
	public:
	~DataDisplayObject() = default;
	DataDisplayObject() = delete;
	DataDisplayObject(const DataDisplayObject & other) = delete;
	DataDisplayObject & operator=(const DataDisplayObject & other) = delete;

	public:
	DataDisplayObject(Pallet & pallet);

	public:
	virtual void	InstancesFullPut(const LogicalData & data) = 0;
	virtual void	InstancesWirePut(const LogicalData & data) = 0;
};
template<typename LogicalData, typename DisplayData> struct TypeDisplayObject : public DataDisplayObject<LogicalData>
{
	public:
	~TypeDisplayObject() = default;
	TypeDisplayObject() = delete;
	TypeDisplayObject(const TypeDisplayObject & other) = delete;
	TypeDisplayObject & operator=(const TypeDisplayObject & other) = delete;

	public:
	TypeDisplayObject(Pallet & pallet);

	private: public:
	Container::Binary<DisplayData>		InstancesFullData;
	Container::Binary<DisplayData>		InstancesWireData;
	public:
	unsigned int	InstancesFullCount() const override;
	unsigned int	InstancesWireCount() const override;
	public:
	void	InstancesFullClear() override;
	void	InstancesWireClear() override;
	public:
	void	InstancesFullPut(const LogicalData & data) override;
	void	InstancesWirePut(const LogicalData & data) override;
	public:
	void	InstancesFullPut(const DisplayData & data);
	void	InstancesWirePut(const DisplayData & data);
	public:
	void	InstancesFullToBuffer() override;
	void	InstancesWireToBuffer() override;
};
};

#endif