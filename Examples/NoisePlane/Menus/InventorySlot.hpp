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

	ItemBase *		Item;
	PolyHedraObject	Object;

	~InventorySlot();
	InventorySlot();

	void	Show();
	void	Hide();

	void	RelayClick(ClickArgs args) override;
};

#endif