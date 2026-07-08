#ifndef  ITEM_CONTAINER_HPP
# define ITEM_CONTAINER_HPP

//# include "ValueType/Vector/U2.hpp"
#include "Generics/Container/Array2D.hpp"

struct ItemBase;

struct ItemContainer
{
	// Array2D
	//VectorU2		Count;
	//ItemBase * *	Data;
	Array2D<ItemBase*>	Items;

	~ItemContainer();
	ItemContainer(VectorU2 count);

	ItemContainer() = delete;
	ItemContainer(const ItemContainer & other) = delete;
	ItemContainer & operator=(const ItemContainer & other) = delete;
};

#endif