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
	void	InstancePutFull(const void * data) override
	{
		InstanceDataFull.Insert(((const TypeData *)data) -> ToData());
	}
	void	InstancePutWire(const void * data) override
	{
		InstanceDataWire.Insert(((const TypeData *)data) -> ToData());
	}
	void	InstancesToBufferFull() override
	{
		//BufferFull.Update();
		BufferFull.DataFull(InstanceDataFull.ToVoid());
	}
	void	InstancesToBufferWire() override
	{
		//BufferWire.Update();
		BufferWire.DataFull(InstanceDataWire.ToVoid());
	}
};
};

#endif