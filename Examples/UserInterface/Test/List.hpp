#ifndef  USER_INTERFACE_TEST_LIST_HPP
# define USER_INTERFACE_TEST_LIST_HPP

# include "Control/_Include.hpp"
# include "Control/Controls/ListBox.hpp"

struct TestList : public UI::Control::Form
{
	UI::Control::ListBox	List;
	UI::Control::Button		ButtonClear;
	UI::Control::Button		ButtonNew;

	~TestList();
	TestList();

	void	ItemFunc(const UI::Control::ListBox::Item & item);

	void	ItemNew(ClickArgs args);
	void	ItemClear(ClickArgs args);
};

#endif