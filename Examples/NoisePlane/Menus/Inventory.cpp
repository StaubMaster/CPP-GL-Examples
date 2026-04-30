#include "Inventory.hpp"



Inventory::~Inventory()
{ }
Inventory::Inventory()
	: UI::Control::Form()
	, Container(nullptr)
{
	VectorF2 SlotSpace(50 + (5 * 2));

	AnchorSize.X = SlotSpace.X * 10 + (5 * 2);
	AnchorSize.Y = SlotSpace.Y * 5 + (5 * 2);

	for (unsigned int y = 0; y < 5; y++)
	{
		for (unsigned int x = 0; x < 10; x++)
		{
			Slots[y][x].Anchor.X.AnchorMin(x * SlotSpace.X);
			Slots[y][x].Anchor.Y.AnchorMin(y * SlotSpace.Y);
			ChildInsert(Slots[y][x]);
		}
	}
}



void Inventory::Change(ItemContainer * container)
{
	Container = container;

	// dont show/hide here
	// bool that says that things changed
	// give Controls a general Update
	// rework Control Internals

	//HideItems();

	if (Container == nullptr)
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
	}

	//ShowItems();
}

#include <iostream>
void Inventory::ShowItems()
{
	for (unsigned int y = 0; y < 5; y++)
	{
		for (unsigned int x = 0; x < 10; x++)
		{
			Slots[y][x].Show();
		}
	}
	std::cout << '\n';
}
void Inventory::HideItems()
{
	for (unsigned int y = 0; y < 5; y++)
	{
		for (unsigned int x = 0; x < 10; x++)
		{
			Slots[y][x].Hide();
		}
	}
}

void Inventory::InsertDrawingEntryRelay()
{
	ShowItems();
}
void Inventory::RemoveDrawingEntryRelay()
{
	HideItems();
}
