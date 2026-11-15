#ifndef  USER_INTERFACE_TEST_LIST_HPP
# define USER_INTERFACE_TEST_LIST_HPP

# include "Control/_Include.hpp"
# include "Control/Controls/ListBox.hpp"

struct TestList : public UI::Control_::Form
{
	UI::Control_::ListBox	List;
	UI::Control_::Button		ButtonClear;
	UI::Control_::Button		ButtonNew;

	~TestList();
	TestList();

	void	ItemFunc(const UI::Control_::ListBox::Item & item);

	void	ItemNew(ClickArgs args);
	void	ItemClear(ClickArgs args);
};

#endif