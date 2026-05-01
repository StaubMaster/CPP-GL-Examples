#include "InventorySlot.hpp"

#include "Item/ItemVoxel.hpp"



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
	AnchorSize = Point2D(50, 50);

	ColorDefault = ColorF4(0.8750f, 0.8750f, 0.8750f);
	ColorHover = ColorF4(0.9375f, 0.9375f, 0.9375f);
}

#include <iostream>
#include "ValueType/_Show.hpp"
void InventorySlot::Show()
{
	if (Item != nullptr && *Item != nullptr)
	{
		ItemVoxel * item = (ItemVoxel*)*Item;
		if (item -> VoxelTemplate != nullptr && item -> VoxelTemplate -> PolyHedra != nullptr)
		{
			VectorF2 PixelSize(40, 40); // hardcoded in Shader
			VectorF2 PixelPos = DisplayBox.Center();
			VectorF2 size = WindowSize.Buffer.SizeFullToNormalRel(PixelSize);
			VectorF2 pos = WindowSize.Buffer.PosFullToNormalRel(PixelPos);

			std::cout << "pos " << pos << '\n'; // removing this breaks PolyHedras ???

			Object.Create(item -> VoxelTemplate -> PolyHedra);
			Object.Trans().Position.X = (+pos.X / size.X);
			Object.Trans().Position.Y = (-pos.Y / size.Y);
			Object.Trans().Rotation.X1 = Angle::Degrees(30);
			Object.Trans().Rotation.Y2 = Angle::Degrees(45);
		}
	}
}
void InventorySlot::Hide()
{
	Object.Delete();
}



void InventorySlot::RelayClick(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		if (Item != nullptr)
		{
			Hide();
			ItemBase * temp = *Item;
			*Item = StaticItem;
			StaticItem = temp;
			Show();
		}
	}
}
