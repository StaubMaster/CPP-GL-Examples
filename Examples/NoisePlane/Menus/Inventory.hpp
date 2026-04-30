#ifndef  INVENTORY_HPP
# define INVENTORY_HPP

# include "Control/Base/Manager.hpp"
# include "ControlsInclude.hpp"

# include "InventorySlot.hpp"
# include "Display/DisplaySize.hpp"

# include "Item/ItemContainer.hpp"

struct Inventory : public UI::Control::Form
{
	ItemContainer *		Container;
	InventorySlot		Slots[5][10];

	~Inventory();
	Inventory();

	void	Change(ItemContainer * container);

	void	ShowItems();
	void	HideItems();

	void	InsertDrawingEntryRelay() override;
	void	RemoveDrawingEntryRelay() override;
	//void UpdateBoxRelay() override;
};

#endif