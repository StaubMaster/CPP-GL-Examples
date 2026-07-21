#ifndef  ITEM_BASE_HPP
# define ITEM_BASE_HPP

struct VectorF2;

/* ItemPallet
Name
Info ?

generic Attributes
*/

/* Item
ItemPallet *
Count
Durability ?

non generic Attributes

Tools would not have Count
Voxels would not have Durability

Item just has Pallet
maybe give it virtual functions for Interactions
*/

struct ItemBase
{
	unsigned int	Count;
	virtual ~ItemBase();
	ItemBase();
};

#endif