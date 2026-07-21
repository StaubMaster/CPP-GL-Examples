#include "InventorySlot.hpp"

#include "Item/ItemVoxel.hpp"

#include "Display/DisplaySize.hpp"



ItemBase * InventorySlot::StaticItem = nullptr;
DisplaySize InventorySlot::WindowSize;



//	ItemBase *		Item;
//	unsigned int	Count;
InventorySlot::~InventorySlot()
{ }
InventorySlot::InventorySlot()
	: UI::Control::Base()
	, Item(nullptr)
{
	AnchorSize = VectorF2(50, 50);

	ColorDefault = ColorF4(0.8750f, 0.8750f, 0.8750f);
	ColorHover = ColorF4(0.9375f, 0.9375f, 0.9375f);
}

#include <iostream>
#include "ValueType/_Show.hpp"

void InventorySlot::RelayUpdateBox()
{
	if (Object.Is())
	{
		Object.Data().Size = VectorF2(40, 40);
		Object.Data().Pos = DisplayBox.Center();
	}
}
void InventorySlot::RelayInsertObject()
{
	if (Item != nullptr && *Item != nullptr)
	{
		ItemVoxel * item = (ItemVoxel*)*Item;
		if (item -> VoxelPallet != nullptr && item -> VoxelPallet -> PolyHedra != nullptr)
		{
			Object.Create(item -> VoxelPallet -> PolyHedra);
			if (Object.Is())
			{
				Object.Data().Size = VectorF2(40, 40);
				Object.Data().Pos = DisplayBox.Center();
				// items should be rotated 45 degrees along Y. and then 30 degrees along X
				// this rotation does X rotation first
				// make angle with Y=45 and X=30 and then .invert() ?
				// .invert() does not exist. it should make it so
				//  ang.forward(p) == ang.invert().reverse(p)
				// but also
				//  ang.reverse(p) == ang.invert().forward(p)
				// not sure if those are mutually exclusive
				Object.Data().Rot.X1 = Angle::Degrees(30);
				Object.Data().Rot.Y2 = Angle::Degrees(45);
			}
		}
	}
}
void InventorySlot::RelayRemoveObject()
{
	Object.Delete();
}



void InventorySlot::RelayClick(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		if (Item != nullptr)
		{
			RelayRemoveObject();
			ItemBase * temp = *Item;
			*Item = StaticItem;
			StaticItem = temp;
			RelayInsertObject();
		}
	}
}
