#include "Inventory.hpp"



InventorySlot & Inventory::operator[](VectorU2 idx)
{
	return Slots[Count.Convert(idx)];
}



Inventory::~Inventory()
{
	delete[] Slots;
}
Inventory::Inventory()
	: UI::Control::Form()
	, Container(nullptr)
	, Count()
	, Slots(nullptr)
{ }



void Inventory::Change(ItemContainer * container)
{
	if (Slots != nullptr) { return; }
	// need to Remove Children



	Container = container;

	Count = Container -> Count;
	Slots = new InventorySlot[Count.Product()];

	VectorF2 SlotSpace(50 + (5 * 2));
	AnchorSize.X = SlotSpace.X * Count.X + (5 * 2);
	AnchorSize.Y = SlotSpace.Y * Count.Y + (5 * 2);

	LoopU2 loop(VectorU2(), Count);
	for (VectorU2 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		unsigned int _u = Count.Convert(u);
		Slots[_u].Anchor.X.AnchorMin(u.X * SlotSpace.X);
		Slots[_u].Anchor.Y.AnchorMin(u.Y * SlotSpace.Y);
		ChildInsert(Slots[_u]);
		Slots[_u].Item = &(*Container)[u];
	}



	// dont show/hide here
	// bool that says that things changed
	// give Controls a general Update
	// rework Control Internals

	//HideItems();

	/*if (Container == nullptr)
	{
		for (unsigned int y = 0; y < 5; y++)
		{
			for (unsigned int x = 0; x < 10; x++)
			{
				Slots[y][x].Item = nullptr;
			}
		}
	}
	else
	{
		for (unsigned int y = 0; y < 5; y++)
		{
			for (unsigned int x = 0; x < 10; x++)
			{
				Slots[y][x].Item = Container -> Items[y][x];
			}
		}
	}*/

	//ShowItems();
}

#include <iostream>
void Inventory::ShowItems()
{
	LoopU2 loop(VectorU2(), Count);
	for (VectorU2 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		Slots[Count.Convert(u)].Show();
	}
	/*for (unsigned int y = 0; y < 5; y++)
	{
		for (unsigned int x = 0; x < 10; x++)
		{
			Slots[y][x].Show();
		}
	}*/
	std::cout << '\n';
}
void Inventory::HideItems()
{
	LoopU2 loop(VectorU2(), Count);
	for (VectorU2 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		Slots[Count.Convert(u)].Hide();
	}
	/*for (unsigned int y = 0; y < 5; y++)
	{
		for (unsigned int x = 0; x < 10; x++)
		{
			Slots[y][x].Hide();
		}
	}*/
}

void Inventory::InsertDrawingEntryRelay()
{
	ShowItems();
}
void Inventory::RemoveDrawingEntryRelay()
{
	HideItems();
}
