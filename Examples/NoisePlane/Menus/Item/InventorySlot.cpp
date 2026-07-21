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



void InventorySlot::RelayUpdateBox()
{
	if (ItemObject.Is())
	{
		ItemObject.Data().Size = VectorF2(40, 40);
		ItemObject.Data().Pos = DisplayBox.Center();
	}
	if (TextObject.Is())
	{
		TextObject.TextPosition() = DisplayBox.Center();
	}
}
void InventorySlot::RelayInsertObject()
{
	if (Item != nullptr && *Item != nullptr)
	{
		ItemVoxel * item = (ItemVoxel*)*Item;
		if (item -> VoxelPallet != nullptr && item -> VoxelPallet -> PolyHedra != nullptr)
		{
			ItemObject.Create(item -> VoxelPallet -> PolyHedra);
			if (ItemObject.Is())
			{
				ItemObject.Data().Size = VectorF2(40, 40);
				ItemObject.Data().Pos = DisplayBox.Center();
				// items should be rotated 45 degrees along Y. and then 30 degrees along X
				// this rotation does X rotation first
				// make angle with Y=45 and X=30 and then .invert() ?
				// .invert() does not exist. it should make it so
				//  ang.forward(p) == ang.invert().reverse(p)
				// but also
				//  ang.reverse(p) == ang.invert().forward(p)
				// not sure if those are mutually exclusive
				ItemObject.Data().Rot.X1 = Angle::Degrees(30);
				ItemObject.Data().Rot.Y2 = Angle::Degrees(45);
			}
			if (Item != nullptr)
			{
				ItemVoxel * item = dynamic_cast<ItemVoxel*>(*Item);
				if (item != nullptr)
				{
					TextObject.Create();
					if (TextObject.Is())
					{
						TextObject.Text() = "";
						TextObject.TextPosition() = DisplayBox.Center();
					}
				}
			}
		}
	}
}
void InventorySlot::RelayRemoveObject()
{
	ItemObject.Delete();
	TextObject.Delete();
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
