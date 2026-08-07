#ifndef  USER_INTERFACE_TEST_LIST_HPP
# define USER_INTERFACE_TEST_LIST_HPP

# include "ControlsInclude.hpp"
# include "Control/List.hpp"

struct TestList : public UI::Control::Form
{
	UI::Control::List	List;

	~TestList();
	TestList();

	void	ItemFunc(void * obj);
};

#endif