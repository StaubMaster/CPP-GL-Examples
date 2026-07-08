#ifndef  NEW_POLYHEDRA_TYPE_PALLET_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_TYPE_PALLET_OBJECT_MANAGER_HPP

# include "../PalletObjectManager.hpp"
# include "Generics/Container/Binary.hpp"

template<
	typename TypeData,
	typename TypeInstanceData
>
struct NewPolyHedra_Type_PalletObjectManager : public NewPolyHedra_PalletObjectManager
{
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
		BufferFull.Update();
		BufferFull.DataFull(InstanceDataFull.ToVoid());
	}
	void	InstancesToBufferWire() override
	{
		BufferWire.Update();
		BufferWire.DataFull(InstanceDataWire.ToVoid());
	}
};

#endif