#ifndef  LIST_FORM_HPP
# define LIST_FORM_HPP

# include "Control/Form.hpp"
# include "Control/Controls/ListBox.hpp"

struct ListForm : public UI::Control_::Form
{
	UI::Control_::ListBox	List;

	void *		Object = nullptr;

	~ListForm();
	ListForm();

	void	ItemFunc(const UI::Control_::ListBox::Item & item);

	/*struct Item : public UI::Control_::Button
	{
		UI::Control_::List &		List;
		void *					Object;
		Item(UI::Control_::List & list, const char * name, void * obj);
		void	Func(ClickArgs args);
	};
	Container::Binary<Item*>	Items;
	void *						Object;
	List();
	void	Clear();
	void	Func(ClickArgs args, void * obj);*/
};

#endif