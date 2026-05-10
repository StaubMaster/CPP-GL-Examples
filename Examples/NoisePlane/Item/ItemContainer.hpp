#ifndef  ITEM_CONTAINER_HPP
# define ITEM_CONTAINER_HPP

# include "ValueType/Vector/U2.hpp"

struct ItemBase;

struct ItemContainer
{
	VectorU2		Count;
	ItemBase * *	Data;

	ItemBase * &	operator[](VectorU2 idx);

	~ItemContainer();
	ItemContainer() = delete;
	ItemContainer(VectorU2 count);
	ItemContainer(const ItemContainer & other) = delete;
	ItemContainer & operator=(const ItemContainer & other) = delete;
};

#endif