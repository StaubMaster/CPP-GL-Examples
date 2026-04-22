#ifndef  CONTEXT_0_MENU_HPP
# define CONTEXT_0_MENU_HPP

# include "ControlsInclude.hpp"

struct Context0Menu : public UI::Control::Form
{
	UI::Control::TextBox	TitleText;

	UI::Control::Button		QuitButton;
	UI::Control::TextBox	QuitText;

	UI::Control::Button		Context0Button;
	UI::Control::TextBox	Context0Text;

	UI::Control::Button		Context1Button;
	UI::Control::TextBox	Context1Text;

	UI::Control::Button		ContextNoisePlaneButton;
	UI::Control::TextBox	ContextNoisePlaneText;

	~Context0Menu();
	Context0Menu();

	void	QuitFunc(ClickArgs args);
	void	Context0Func(ClickArgs args);
	void	Context1Func(ClickArgs args);
	void	ContextNoisePlaneFunc(ClickArgs args);
};

#endif