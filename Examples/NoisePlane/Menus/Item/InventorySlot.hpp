#ifndef  INVENTORY_SLOT_HPP
# define INVENTORY_SLOT_HPP

# include "Control/Base/Manager.hpp"
# include "ControlsInclude.hpp"

# include "PolyHedra/Object.hpp"

struct ItemBase;

struct InventorySlot : public UI::Control::Base
{
	static ItemBase *	StaticItem;
	static DisplaySize	WindowSize;

	ItemBase **		Item; // ItemContainer holds Item Pointers, this is a Pointer to that
	PolyHedraObject	Object;

	~InventorySlot();
	InventorySlot();

	void	InsertDrawingEntryRelay() override;
	void	RemoveDrawingEntryRelay() override;
	void	UpdateBoxRelay() override;

	void	RelayClick(ClickArgs args) override;
};

#endif