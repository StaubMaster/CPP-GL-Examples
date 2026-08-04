#ifndef  USER_INTERFACE_TEST_SCROLL_HPP
# define USER_INTERFACE_TEST_SCROLL_HPP

# include "ControlsInclude.hpp"

class ScrollBox : public UI::Control::Base
{
	public:
	UI::Control::Slider		ScrollBar;

	public:
	~ScrollBox();
	ScrollBox();

	public:
	void	RelayUpdateBox() override;

	public:
	void	CalcScroll();
	void	ScrollFunc(float val);
};

struct TestScroll : public UI::Control::Form
{
	ScrollBox	ScrollBox;

	UI::Control::Label *	Labels;

	~TestScroll();
	TestScroll();
};

#endif