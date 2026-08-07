#ifndef  UI_CONTROL_LIST_HPP
# define UI_CONTROL_LIST_HPP

# include "Control/General/Base.hpp"
# include "Control/General/BaseText.hpp"
# include "Control/ScrollBox.hpp"

# include "Generics/Function/Pointer.hpp"
# include "Generics/Container/Binary.hpp"

namespace UI
{
namespace Control
{
struct List : public UI::Control::ScrollBox
{
	struct Item : public UI::Control::BaseText
	{
		UI::Control::List &		List;

		unsigned int	Index;

		void *	Object;

		Item(UI::Control::List & list, unsigned int idx , const char * name, void * obj);

		void	RelayClick(ClickArgs args) override;
	};

	Container::Binary<Item*>	Items; // these are already stored in Children
	// Children are (Base*) this is (Item*)

	void *		ClickedObject = nullptr;

	FunctionPointer<const Item &>	ItemFunc;

	List();

	void	ItemsClear();
	void	ItemNew(const char * name, void * obj);

	void	ItemClickFunc(ClickArgs args, const Item & item);
};
};
};

#endif