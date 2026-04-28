#ifndef  INVENTORY_SLOT_HPP
# define INVENTORY_SLOT_HPP

# include "Control/Base/Manager.hpp"
# include "ControlsInclude.hpp"

struct ItemBase;

struct InventorySlot : public UI::Control::Base
{
	ItemBase *		Item;
	~InventorySlot();
	InventorySlot();
	void	Show(VectorF2 pos);
	void	Hide();
};

#endif