/*#ifndef  HOT_BAR_HPP
# define HOT_BAR_HPP

# include "Control/Base/Manager.hpp"
# include "ControlsInclude.hpp"

# include "InventorySlot.hpp"
# include "Display/DisplaySize.hpp"

# include "ValueType/Vector/U2.hpp"
# include "Item/ItemContainer.hpp"

struct HotBar : public UI::Control::Form
{
	ItemContainer *		Container;

	VectorU2			Count;
	InventorySlot *		Slots;

	InventorySlot &		operator[](VectorU2 idx);

	~HotBar();
	HotBar();

	void	Change(ItemContainer * container);

	void	ShowItems();
	void	HideItems();

	void	InsertDrawingEntryRelay() override;
	void	RemoveDrawingEntryRelay() override;
	//void UpdateBoxRelay() override;
};

#endif*/