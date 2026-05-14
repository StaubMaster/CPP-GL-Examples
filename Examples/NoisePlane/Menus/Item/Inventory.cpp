#include "Inventory.hpp"



Inventory::~Inventory()
{ }
Inventory::Inventory()
	: UI::Control::Form()
	, Container(nullptr)
	, Slots()
{ }



#include <iostream>
void Inventory::Change(ItemContainer * container)
{
	if (!Slots.IsNull()) { return; }
	// need to Remove Children



	Container = container;

	Slots.Size(Container -> Items.Size());

	VectorF2 SlotSpace(50 + (5 * 2));
	AnchorSize.X = SlotSpace.X * Slots.Size().X + (5 * 2);
	AnchorSize.Y = SlotSpace.Y * Slots.Size().Y + (5 * 2);

	LoopU2 loop(VectorU2(), Slots.Size());
	for (VectorU2 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		unsigned int _u = Slots.Size().Convert(u);
		Slots[_u].Anchor.X.AnchorMin(u.X * SlotSpace.X);
		Slots[_u].Anchor.Y.AnchorMin(u.Y * SlotSpace.Y);
		ChildInsert(Slots[_u]);
		Slots[_u].Item = &(Container -> Items[u]);
	}
}

#include <iostream>
void Inventory::ShowItems()
{
	LoopU2 loop(VectorU2(), Slots.Size());
	for (VectorU2 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		Slots[u].Show();
	}
	std::cout << '\n';
}
void Inventory::HideItems()
{
	LoopU2 loop(VectorU2(), Slots.Size());
	for (VectorU2 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		Slots[u].Hide();
	}
}

void Inventory::RelayInsertObject()
{
	ShowItems();
}
void Inventory::RelayRemoveObject()
{
	HideItems();
}
