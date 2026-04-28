#ifndef  INVENTORY_HPP
# define INVENTORY_HPP

# include "Control/Base/Manager.hpp"
# include "ControlsInclude.hpp"

# include "InventorySlot.hpp"
# include "Display/DisplaySize.hpp"

struct Inventory : public UI::Control::Form
{
	static DisplaySize	WindowSize;

	InventorySlot	Slots[5][10];
	~Inventory();
	Inventory();

	void	InsertDrawingEntryRelay() override;
	void	RemoveDrawingEntryRelay() override;
	//void UpdateBoxRelay() override;
};

#endif