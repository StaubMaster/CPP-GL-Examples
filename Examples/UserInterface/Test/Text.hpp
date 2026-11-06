#ifndef  USER_INTERFACE_TEST_TEXT_HPP
# define USER_INTERFACE_TEST_TEXT_HPP

# include "Control/_Include.hpp"

struct TestText : public UI::Control::Form
{
	UI::Control::Slider		Align;
	UI::Control::TextBox	Text;

	TestText();

	void	AlignFunc(VectorF2 val);
};

#endif