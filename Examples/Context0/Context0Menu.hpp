#ifndef  CONTEXT_0_MENU_HPP
# define CONTEXT_0_MENU_HPP

# include "ControlsInclude.hpp"

struct Context0Menu : public UI::Control::Form
{
	UI::Control::TextBox	TitleText;

	UI::Control::Button		QuitButton;
	UI::Control::Button		Context0Button;
	UI::Control::Button		Context1Button;
	UI::Control::Button		ContextNoisePlaneButton;
	UI::Control::Button		ContextTestTextAlignmentButton;

	~Context0Menu();
	Context0Menu();

	void	QuitFunc(ClickArgs args);
	void	Context0Func(ClickArgs args);
	void	Context1Func(ClickArgs args);
	void	ContextNoisePlaneFunc(ClickArgs args);
	void	ContextTestTextAlignmentFunc(ClickArgs args);
};

#endif