#ifndef  ITEM_CONTAINER_HPP
# define ITEM_CONTAINER_HPP

struct ItemBase;

struct ItemContainer
{
	ItemBase *		Items[5][10];

	~ItemContainer();
	ItemContainer();
};

#endif