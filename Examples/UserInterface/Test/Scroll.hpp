#ifndef  USER_INTERFACE_TEST_SCROLL_HPP
# define USER_INTERFACE_TEST_SCROLL_HPP

# include "Control/_Include.hpp"
# include "Control/Controls/ScrollBox.hpp"

struct TestScroll : public UI::Control_::Form
{
	UI::Control_::ScrollBox		ScrollBox;
	UI::Control_::Label *		Labels;

	~TestScroll();
	TestScroll();
};

#endif