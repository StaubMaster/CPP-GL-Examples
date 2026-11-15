#ifndef  UI_CONTROL_LIST_BOX_HPP
# define UI_CONTROL_LIST_BOX_HPP

# include "Control/General/Base.hpp"
# include "Control/General/BaseText.hpp"
# include "Control/Controls/ScrollBox.hpp"

# include "Generics/Function/Pointer.hpp"
# include "Generics/Container/Binary.hpp"

namespace UI
{
namespace Control_
{
struct ListBox : public ScrollBox
{
	struct Item : public BaseText // rename to ListItem, make not nested
	{
		ListBox &		ListBox_;
		unsigned int	Index;

		void *	Object;

		~Item() = default;
		Item() = delete;
		Item(const Item & other) = delete;
		Item & operator=(const Item & other) = delete;

		Item(ListBox & listBox, unsigned int idx , const char * name, void * obj);

		void	RelayClick(ClickArgs args) override;
	};
	Container::Binary<Item*>	Items;

	void *		ClickedObject = nullptr;

	Function::Pointer<const Item &>		ItemFunc;

	~ListBox();
	ListBox();

	void	ItemsClear();
	void	ItemNew(const char * name, void * obj);

	void	ItemClickFunc(ClickArgs args, const Item & item);
};
};
};

#endif