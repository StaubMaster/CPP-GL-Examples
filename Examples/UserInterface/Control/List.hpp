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

		void *	Object;

		Item(UI::Control::List & list, const char * name, void * obj);

		void	RelayClick(ClickArgs args) override;
	};

	Container::Binary<Item*>	Items; // these are already stored in Children
	// Children are (Base*) this is (Item*)

	void *		ClickedObject = nullptr;

	FunctionPointer<void*>	ItemClickFunc;

	List();

	void	ItemsClear();
	void	ItemNew(const char * name, void * obj);
	void	ClickFunc(ClickArgs args, void * obj);
};
};
};

#endif