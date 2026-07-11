#ifndef  INVENTORY_SLOT_HPP
# define INVENTORY_SLOT_HPP

# include "Control/General/Manager.hpp"
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

	protected:
	void	RelayUpdateBox() override;
	void	RelayInsertObject() override;
	void	RelayRemoveObject() override;

	void	RelayClick(ClickArgs args) override;
};

#endif