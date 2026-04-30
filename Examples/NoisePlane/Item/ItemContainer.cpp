#include "Item/ItemContainer.hpp"
#include "ValueType/UndexLoop2D.hpp"



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
	UndexLoop2D loop(VectorU2(), Count);
	for (VectorU2 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		Data[Count.Convert(u)] = nullptr;
	}
}
