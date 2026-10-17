#ifndef  ITEM_CONTAINER_UI_HPP
# define ITEM_CONTAINER_UI_HPP

# include "Control/Form.hpp"

# include "Item/ItemContainer.hpp"

# include "ItemSlotUI.hpp"
# include "Generics/Container/Array2D.hpp"

struct ItemContainerUI : public UI::Control::Form
{
	ItemContainer *			Container;
	Array2D<ItemSlotUI>		Slots;

	/* Slot Indicator ?
		use Index to Indicate any Slot
		use None to hide Indicator
	*/

	~ItemContainerUI();
	ItemContainerUI();

	void	Change(ItemContainer * container);

	void	ShowItems();
	void	HideItems();

	void	DisplayShow() override;
	void	DisplayHide() override;
};

#endif