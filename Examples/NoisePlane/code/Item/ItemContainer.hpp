#ifndef  ITEM_CONTAINER_HPP
# define ITEM_CONTAINER_HPP

#include "Generics/Container/Array2D.hpp"

struct ItemBase;

struct ItemContainer
{
	Array2D<ItemBase*>	Items;

	~ItemContainer();
	ItemContainer(VectorU2 count);

	ItemContainer() = delete;
	ItemContainer(const ItemContainer & other) = delete;
	ItemContainer & operator=(const ItemContainer & other) = delete;
};

#endif