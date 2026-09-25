#ifndef  NEW_POLYHEDRA_TYPE_PALLET_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_TYPE_PALLET_OBJECT_MANAGER_HPP

# include "../PalletObjectManager.hpp"
# include "Generics/Container/Binary.hpp"

namespace NewPolyHedra
{
template<typename TypeData, typename TypeInstanceData>
struct Type_PalletObjectManager : public PalletObjectManager
{
	public:
	~Type_PalletObjectManager() = default;
	Type_PalletObjectManager() = default;
	Type_PalletObjectManager(const Type_PalletObjectManager & other) = delete;
	Type_PalletObjectManager & operator=(const Type_PalletObjectManager & other) = delete;

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