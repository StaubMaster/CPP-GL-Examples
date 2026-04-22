#ifndef  CONTEXT_1_MENU_HPP
# define CONTEXT_1_MENU_HPP

# include "ControlsInclude.hpp"

struct Context1Menu : public UI::Control::Form
{
	UI::Control::TextBox	TitleText;

	UI::Control::TextBox	QuitText;
	UI::Control::Button		QuitButton;

	UI::Control::TextBox	Context0Text;
	UI::Control::Button		Context0Button;

	UI::Control::TextBox	Context1Text;
	UI::Control::Button		Context1Button;

	~Context1Menu();
	Context1Menu();

	void	QuitFunc(ClickArgs args);
	void	Context0Func(ClickArgs args);
	void	Context1Func(ClickArgs args);
};

#endif