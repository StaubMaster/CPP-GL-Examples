#ifndef  NEW_POLYHEDRA_TYPE_DISPLAY_DATA_HPP
# define NEW_POLYHEDRA_TYPE_DISPLAY_DATA_HPP

# include "NewPolyHedra/Base/Display/Data.hpp"

# include "Generics/Container/Binary.hpp"

namespace NewPolyHedra
{
template<typename TypeData, typename TypeInstanceData>
struct TypeDisplayData : public BaseDisplayData
{
	public:
	~TypeDisplayData() = default;
	TypeDisplayData() = delete;
	TypeDisplayData(const TypeDisplayData & other) = delete;
	TypeDisplayData & operator=(const TypeDisplayData & other) = delete;

	public:
	TypeDisplayData(Pallet & pallet);

	private:
	Container::Binary<TypeInstanceData>		InstancesFullData;
	Container::Binary<TypeInstanceData>		InstancesWireData;
	public:
	unsigned int	InstancesFullCount() const override;
	unsigned int	InstancesWireCount() const override;
	public:
	void	InstancesFullClear() override;
	void	InstancesWireClear() override;
	public:
	void	InstancesFullPut(const void * data) override;
	void	InstancesWirePut(const void * data) override;
	private:
	void	InstancesFullPut(const TypeData & data);
	void	InstancesWirePut(const TypeData & data);
	private:
	void	InstancesFullPut(const TypeInstanceData & data);
	void	InstancesWirePut(const TypeInstanceData & data);
	public:
	void	InstancesFullToBuffer() override;
	void	InstancesWireToBuffer() override;
};
};

#endif