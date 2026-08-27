#include "ItemSlotUI.hpp"

#include "Item/ItemVoxel.hpp"
#include "Item/ItemTool.hpp"

#include "Display/DisplaySize.hpp"



ItemBase *		ItemSlotUI::StaticItem = nullptr;
DisplaySize		ItemSlotUI::WindowSize;



//	ItemBase *		Item;
//	unsigned int	Count;
ItemSlotUI::~ItemSlotUI()
{ }
ItemSlotUI::ItemSlotUI()
	: UI::Control::Base()
	, Item(nullptr)
{
	AnchorSize = VectorF2(50, 50);

	ColorDefault = ColorF4(0.8750f, 0.8750f, 0.8750f);
	ColorHover = ColorF4(0.9375f, 0.9375f, 0.9375f);
}



void ItemSlotUI::BoxUpdate()
{
	Base::BoxUpdate();
	if (ItemObject.Is())
	{
		ItemObject.Data().Pos = BoxDisplay.Center();
	}
	if (TextObject.Is())
	{
		TextObject.TextPosition() = BoxDisplay.Center();
	}
}
void ItemSlotUI::ObjectInsert()
{
	Base::ObjectInsert();
	if (Item != nullptr)
	{
		{
			ItemVoxel * item = dynamic_cast<ItemVoxel*>(*Item);
			if (item != nullptr && item -> VoxelPallet != nullptr && item -> VoxelPallet -> PolyHedra != nullptr)
			{
				ItemObject.Create(item -> VoxelPallet -> PolyHedra);
				if (ItemObject.Is())
				{
					ItemObject.Data().Size = VectorF2(32, 32);
					ItemObject.Data().Pos = BoxDisplay.Center();
					ItemObject.Data().Rot = EulerAngle3D::Degrees(0, 30, 45).reverse();
				}
				TextObject.Create();
				if (TextObject.Is())
				{
					TextObject.Text() = "";
					TextObject.TextPosition() = BoxDisplay.Center();
				}
			}
		}
		{
			ItemTool * item = dynamic_cast<ItemTool*>(*Item);
			if (item != nullptr && item -> Pallet != nullptr)
			{
				ItemObject.Create(item -> Pallet);
				if (ItemObject.Is())
				{
					ItemObject.Data().Size = VectorF2(32, 32);
					// this scales the [-1;+1] box
					// but anything outside of the box is still culled
					// just give everything a seperate scale factor ?
					// also depth in general is wrong
					ItemObject.Data().Pos = BoxDisplay.Center();
					ItemObject.Data().Rot = EulerAngle3D::Degrees(0, 30, 45).reverse();
					ItemObject.Data().Scale = 0.25f;
				}
				TextObject.Create();
				if (TextObject.Is())
				{
					TextObject.Text() = "";
					TextObject.TextPosition() = BoxDisplay.Center();
				}
			}
		}
	}
}
void ItemSlotUI::ObjectRemove()
{
	Base::ObjectRemove();
	ItemObject.Delete();
	TextObject.Delete();
}



void ItemSlotUI::RelayClick(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		if (Item != nullptr)
		{
			ObjectRemove();
			ItemBase * temp = *Item;
			*Item = StaticItem;
			StaticItem = temp;
			ObjectInsert();
		}
	}
}
