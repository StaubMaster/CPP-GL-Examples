#ifndef  NEW_POLYHEDRA_TYPE_PALLET_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_TYPE_PALLET_OBJECT_MANAGER_HPP

# include "PalletObjectManager.hpp"
# include "ObjectData.hpp"

template<
	typename TypeData,
	typename TypeInstanceData
>
struct NewPolyHedra_Type_PalletObjectManager : public NewPolyHedra_PalletObjectManager
{
	Container::Binary<TypeInstanceData>		InstanceData;

	// InstanceData can not be done with Poitners
	// so it needs to be specified with Template

	// accumulate InstanceData using BlockList
	// InstancesDone() to turn BlockList into Array

	void	InstancesClear() override
	{
		InstanceData.Clear();
	}
	void	InstancePut(const NewPolyHedra_ObjectData & data) override
	{
		InstancePut(&data);
	}
	void	InstancePut(const NewPolyHedra_ObjectData * data) override
	{
		InstanceData.Insert(((const NewPolyHedra_Type_ObjectData<TypeData> *)data) -> Data.ToData());
	}
	void	InstancesToBuffer() override
	{
		Buffer.Update();
		Buffer.DataFull(InstanceData.ToVoid());
	}
};

#endif