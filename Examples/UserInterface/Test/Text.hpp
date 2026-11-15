#ifndef  USER_INTERFACE_TEST_TEXT_HPP
# define USER_INTERFACE_TEST_TEXT_HPP

# include "Control/_Include.hpp"

struct TestText : public UI::Control_::Form
{
	UI::Control_::Slider		Align;
	UI::Control_::TextBox	Text;

	TestText();

	void	AlignFunc(VectorF2 val);
};

#endif