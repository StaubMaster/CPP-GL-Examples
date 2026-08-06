#ifndef  USER_INTERFACE_TEST_SCROLL_HPP
# define USER_INTERFACE_TEST_SCROLL_HPP

# include "ControlsInclude.hpp"
# include "Control/ScrollBox.hpp"

struct TestScroll : public UI::Control::Form
{
	UI::Control::ScrollBox		ScrollBox;
	UI::Control::Label *		Labels;

	~TestScroll();
	TestScroll();
};

#endif