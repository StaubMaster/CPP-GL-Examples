#ifndef  USER_INTERFACE_MENU_0_HPP
# define USER_INTERFACE_MENU_0_HPP

# include "ControlsInclude.hpp"

struct UserInterfaceMenu0 : public UI::Control::Form
{
	UI::Control::Label		TitleText;
	UI::Control::Button		QuitButton;
	UI::Control::Button		ReButton;
	UI::Control::Button		BackButton;

	UI::Control::Button		Menu1Button;
	UI::Control::Button		Menu2Button;
	UI::Control::Button		Menu3Button;

	~UserInterfaceMenu0();
	UserInterfaceMenu0();

	void	QuitFunc(ClickArgs args);
	void	ReFunc(ClickArgs args);
	void	BackFunc(ClickArgs args);
};

#endif