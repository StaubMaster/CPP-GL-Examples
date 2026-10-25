#include "NewPolyHedra/Type/Logical/ObjectManager.hpp"
#include "NewPolyHedra/Type/Logical/Object.hpp"

#include "NewPolyHedra/Type/Display/ObjectManager.hpp"

#include "NewPolyHedra/Pallet/Manager.hpp"

#include "Generics/Loop.hpp"



template<typename LogicalData> NewPolyHedra::TypeLogicalObjectManager<LogicalData> * NewPolyHedra::TypeLogicalObjectManager<LogicalData>::Current = nullptr;

template<typename LogicalData> NewPolyHedra::TypeLogicalObject<LogicalData> * NewPolyHedra::TypeLogicalObjectManager<LogicalData>::sNew(Pallet & pallet)
{
	if (Current == nullptr) { return nullptr; }
	return &(Current -> New(pallet));
}
template<typename LogicalData> NewPolyHedra::TypeLogicalObject<LogicalData> * NewPolyHedra::TypeLogicalObjectManager<LogicalData>::sNew(Pallet * pallet)
{
	if (pallet == nullptr) { return nullptr; }
	if (Current == nullptr) { return nullptr; }
	return &(Current -> New(*pallet));
}



template<typename LogicalData> NewPolyHedra::TypeLogicalObjectManager<LogicalData>::~TypeLogicalObjectManager()
{
	Current = nullptr;
}
template<typename LogicalData> NewPolyHedra::TypeLogicalObjectManager<LogicalData>::TypeLogicalObjectManager()
{
	Current = this;
}



template<typename LogicalData> unsigned int NewPolyHedra::TypeLogicalObjectManager<LogicalData>::Count() const
{
	return Objects.Count();
}



template<typename LogicalData> NewPolyHedra::TypeLogicalObject<LogicalData> & NewPolyHedra::TypeLogicalObjectManager<LogicalData>::New(Pallet & pallet)
{
	TypeLogicalObject<LogicalData> * object = new TypeLogicalObject<LogicalData>();
	object -> DisplayObject = DataDisplayObjectManager<LogicalData>::sTake(pallet);
	this -> Objects.Insert(object);
	return *object;
}



template<typename LogicalData> void NewPolyHedra::TypeLogicalObjectManager<LogicalData>::Clean()
{
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		BaseLogicalObject * object = Objects[i];
		if (object == nullptr)
		{
			Objects.RemoveAt(i);
			i--;
		}
		else if (object -> Remove)
		{
			delete object;
			Objects.RemoveAt(i);
			i--;
		}
	}
}

template<typename LogicalData> void NewPolyHedra::TypeLogicalObjectManager<LogicalData>::InstancesMake()
{
	Container::Loop::Invoke(Objects, &NewPolyHedra::BaseLogicalObject::InstancePut);
}
