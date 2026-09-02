#ifndef  UI_CONTROL_LIST_BOX_HPP
# define UI_CONTROL_LIST_BOX_HPP

# include "Control/General/Base.hpp"
# include "Control/General/BaseText.hpp"
# include "Control/Controls/ScrollBox.hpp"

# include "Generics/Function/Pointer.hpp"
# include "Generics/Container/Binary.hpp"

namespace UI
{
namespace Control
{
struct ListBox : public UI::Control::ScrollBox
{
	struct Item : public UI::Control::BaseText
	{
		UI::Control::ListBox &		ListBox;
		unsigned int	Index;

		void *	Object;

		~Item();
		Item() = delete;
		Item(const Item & other) = delete;
		Item & operator=(const Item & other) = delete;

		Item(UI::Control::ListBox & listBox, unsigned int idx , const char * name, void * obj);

		void	RelayClick(ClickArgs args) override;
	};
	Container::Binary<Item*>	Items;

	void *		ClickedObject = nullptr;

	FunctionPointer<const Item &>	ItemFunc;

	~ListBox();
	ListBox();

	void	ItemsClear();
	void	ItemNew(const char * name, void * obj);

	void	ItemClickFunc(ClickArgs args, const Item & item);
};
};
};

#endif