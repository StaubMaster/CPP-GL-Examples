#include "InventorySlot.hpp"
#include "Inventory/ItemBase.hpp"



//	ItemBase *		Item;
//	unsigned int	Count;
InventorySlot::~InventorySlot()
{ }
InventorySlot::InventorySlot()
	: UI::Control::Base()
	, Item(nullptr)
{
	AnchorSize = Point2D(40, 40);
}



void InventorySlot::Show(VectorF2 pos)
{
	if (Item != nullptr)
	{
		Item -> Show(pos);
	}
}
void InventorySlot::Hide()
{
	if (Item != nullptr)
	{
		Item -> Hide();
	}
}
