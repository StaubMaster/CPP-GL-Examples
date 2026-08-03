#ifndef  ITEM_CONTAINER_UI_HPP
# define ITEM_CONTAINER_UI_HPP

# include "Control/Form.hpp"

# include "Item/ItemContainer.hpp"

# include "ItemSlotUI.hpp"
# include "Generics/Container/Array2D.hpp"

struct ItemContainerUI : public UI::Control::Form
{
	ItemContainer *			Container;
	Array2D<ItemSlotUI>	Slots;

	~ItemContainerUI();
	ItemContainerUI();

	void	Change(ItemContainer * container);

	void	ShowItems();
	void	HideItems();

	void	RelayInsertObject() override;
	void	RelayRemoveObject() override;
};

#endif