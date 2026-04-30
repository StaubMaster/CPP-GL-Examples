#include "Item/ItemContainer.hpp"


ItemContainer::~ItemContainer()
{ }
ItemContainer::ItemContainer()
{
	for (unsigned int y = 0; y < 5; y++)
	{
		for (unsigned int x = 0; x < 10; x++)
		{
			Items[y][x] = nullptr;
		}
	}
}
