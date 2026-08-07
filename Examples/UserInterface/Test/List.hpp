#ifndef  USER_INTERFACE_TEST_LIST_HPP
# define USER_INTERFACE_TEST_LIST_HPP

# include "ControlsInclude.hpp"
# include "Control/List.hpp"

struct TestList : public UI::Control::Form
{
	UI::Control::List	List;

	UI::Control::Button	ButtonClear;
	UI::Control::Button	ButtonNew;

	~TestList();
	TestList();

	void	ItemFunc(const UI::Control::List::Item & item);

	void	ItemClear(ClickArgs args);
	void	ItemNew(ClickArgs args);
};

#endif