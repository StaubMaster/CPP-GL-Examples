#ifndef  INVENTORY_HPP
# define INVENTORY_HPP

# include "Control/Base/Manager.hpp"
# include "ControlsInclude.hpp"

# include "InventorySlot.hpp"
# include "Display/DisplaySize.hpp"

# include "ValueType/Vector/U2.hpp"
# include "Item/ItemContainer.hpp"

# include "Miscellaneous/Container/Array2D.hpp"

struct Inventory : public UI::Control::Form
{
	ItemContainer *		Container;

	// Array2D
//	VectorU2			Count;
//	InventorySlot *		Slots;
	Array2D<InventorySlot>	Slots;

//	InventorySlot &		operator[](VectorU2 idx);

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