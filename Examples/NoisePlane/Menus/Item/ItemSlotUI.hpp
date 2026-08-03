#ifndef  ITEM_SLOT_UI_HPP
# define ITEM_SLOT_UI_HPP

# include "Control/Form.hpp"
# include "Text/Object.hpp"

# include "NewPolyHedraUI.hpp"

struct ItemBase;

struct ItemSlotUI : public UI::Control::Base
{
	static ItemBase *	StaticItem;
	static DisplaySize	WindowSize;

	ItemBase **		Item; // ItemContainer holds Item Pointers, this is a Pointer to that
	NewPolyHedra::UserInterface::Object		ItemObject;
	UI::Text::Object						TextObject; // Text is not in front of ItemObject

	~ItemSlotUI();
	ItemSlotUI();

	// should spin
	// all spin syncronized
	// do spin with Uniform ?
	// what if I want other UI::PolyHedra with independant spin ?
	// if this is done with Uniform, then there is no rotation in VertexData
	// so it is seperate

	protected:
	void	RelayUpdateBox() override;
	void	RelayInsertObject() override;
	void	RelayRemoveObject() override;

	void	RelayClick(ClickArgs args) override;
};

#endif