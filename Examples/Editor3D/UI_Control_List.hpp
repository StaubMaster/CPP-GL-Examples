#ifndef  LIST_FORM_HPP
# define LIST_FORM_HPP

# include "Control/Form.hpp"
# include "Control/ListBox.hpp"

struct ListForm : public UI::Control::Form
{
	UI::Control::ListBox	List;

	void *		Object = nullptr;

	~ListForm();
	ListForm();

	void	ItemFunc(const UI::Control::ListBox::Item & item);

	/*struct Item : public UI::Control::Button
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
	void	Func(ClickArgs args, void * obj);*/
};

#endif