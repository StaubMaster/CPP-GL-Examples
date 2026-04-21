#ifndef  MAIN_MENU_HPP
# define MAIN_MENU_HPP

# include "Control/Base/Manager.hpp"
# include "ControlsInclude.hpp"

struct MainMenu : public UI::Control::Form
{
	UI::Control::Button		ButtonPlay;
	UI::Control::Button		ButtonTerminate;

	~MainMenu();
	MainMenu();
};

#endif