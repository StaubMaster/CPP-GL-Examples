#ifndef  NEW_POLYHEDRA_TYPE_PALLET_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_TYPE_PALLET_OBJECT_MANAGER_HPP

# include "PalletObjectManager.hpp"
# include "ObjectData.hpp"

template<typename DataType, typename TypeInstanceData>
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
		const NewPolyHedra_Type_ObjectData<DataType> * type_data = dynamic_cast<const NewPolyHedra_Type_ObjectData<DataType> *>(data);
		if (type_data != nullptr)
		{
			InstanceData.Insert(type_data -> Data.ToData());
		}
	}
};

#endif