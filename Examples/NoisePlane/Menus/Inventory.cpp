#include "Inventory.hpp"



DisplaySize Inventory::WindowSize;



Inventory::~Inventory()
{ }
Inventory::Inventory()
	: UI::Control::Form()
{
	VectorF2 SlotSpace(40 + (5 * 2));

	AnchorSize.X = SlotSpace.X * 10 + (5 * 2);
	AnchorSize.Y = SlotSpace.Y * 5 + (5 * 2);

	float x = 0;
	float y = 0;
	for (unsigned int iy = 0; iy < 5; iy++)
	{
		y = iy * SlotSpace.Y;
		for (unsigned int ix = 0; ix < 10; ix++)
		{
			x = ix * SlotSpace.X;
			Slots[iy][ix].Anchor.X.AnchorMin(x);
			Slots[iy][ix].Anchor.Y.AnchorMin(y);
			ChildInsert(Slots[iy][ix]);
		}
	}
}

#include <iostream>
#include "ValueType/_Show.hpp"
void Inventory::InsertDrawingEntryRelay()
{
	VectorF2	PixelSize(40, 40); // hardcoded in Shader
	VectorF2	size = WindowSize.Buffer.SizeFullToNormalRel(PixelSize);

	for (unsigned int iy = 0; iy < 5; iy++)
	{
		for (unsigned int ix = 0; ix < 10; ix++)
		{
			VectorF2 center = Slots[iy][ix].DisplayBox.Center();

			VectorF2 pos = WindowSize.Buffer.PosFullToNormalRel(center);
			std::cout << "center  : " << center << '\n';
			std::cout << "pos     : " << (pos) << '\n';
			std::cout << "size    : " << (size) << '\n';
			std::cout << "pos/size: " << (pos / size) << '\n';
			Slots[iy][ix].Show(pos / size);
		}
	}
	std::cout << '\n';
}
void Inventory::RemoveDrawingEntryRelay()
{
	for (unsigned int iy = 0; iy < 5; iy++)
	{
		for (unsigned int ix = 0; ix < 10; ix++)
		{
			Slots[iy][ix].Hide();
		}
	}
}

