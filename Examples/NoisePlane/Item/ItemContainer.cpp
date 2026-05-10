#include "Item/ItemContainer.hpp"
#include "ValueType/LoopU2.hpp"



ItemBase * & ItemContainer::operator[](VectorU2 idx)
{
	return Data[Count.Convert(idx)];
}



ItemContainer::~ItemContainer()
{
	delete[] Data;
}
ItemContainer::ItemContainer(VectorU2 count)
	: Count(count)
	, Data(new ItemBase*[Count.Product()])
{
	LoopU2 loop(VectorU2(), Count);
	for (VectorU2 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		Data[Count.Convert(u)] = nullptr;
	}
}
