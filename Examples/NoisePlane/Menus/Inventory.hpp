#ifndef  INVENTORY_HPP
# define INVENTORY_HPP

# include "Control/Base/Manager.hpp"
# include "ControlsInclude.hpp"

# include "InventorySlot.hpp"

struct Inventory : public UI::Control::Form
{
	Slots	InventorySlot[5][10];
	Inventory();
};

#endif