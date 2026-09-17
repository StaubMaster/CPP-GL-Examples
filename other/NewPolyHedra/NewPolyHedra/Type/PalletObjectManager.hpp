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
	Container::Binary<TypeInstanceData>		InstanceDataFull;
	Container::Binary<TypeInstanceData>		InstanceDataWire;

	public:
	void	InstancesClear() override
	{
		InstanceDataFull.Clear();
		InstanceDataWire.Clear();
	}
	void	InstancePutFull(const void * data) override { InstancePutFull(*((const TypeData *)data)); }
	void	InstancePutWire(const void * data) override { InstancePutFull(*((const TypeData *)data)); }
	void	InstancePutFull(const TypeData & data) { InstancePutFull(TypeInstanceData(data)); }
	void	InstancePutWire(const TypeData & data) { InstancePutWire(TypeInstanceData(data)); }
	void	InstancePutFull(const TypeInstanceData & data) { InstanceDataFull.Insert(data); }
	void	InstancePutWire(const TypeInstanceData & data) { InstanceDataWire.Insert(data); }
	void	InstancesToBufferFull() override
	{
		BufferFullInstance.DataFull(InstanceDataFull.ToVoid());
		CountFull = InstanceDataFull.Count();
	}
	void	InstancesToBufferWire() override
	{
		BufferWireInstance.DataFull(InstanceDataWire.ToVoid());
		CountWire = InstanceDataWire.Count();
	}
};
};

#endif