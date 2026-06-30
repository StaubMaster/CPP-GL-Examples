#ifndef  UI_CONTROL_LIST
# define UI_CONTROL_LIST

# include "Control/Form.hpp"
# include "Control/Button.hpp"
# include "Miscellaneous/Container/Binary.hpp"

namespace UI
{
namespace Control
{
struct List : public UI::Control::Form
{
	struct Item : public UI::Control::Button
	{
		UI::Control::List &		List;
		void *					Object;
		Item(UI::Control::List & list, const char * name, void * obj);
		void	Func(ClickArgs args);
	};
	Container::Binary<Item*>	Items;
	void *						Object;
	List();
	void	Clear();
	void	Func(ClickArgs args, void * obj);
};
};
};

#endif