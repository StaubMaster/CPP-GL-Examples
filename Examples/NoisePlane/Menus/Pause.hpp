#ifndef  PAUSE_MENU_HPP
# define PAUSE_MENU_HPP

# include "Control/Base/Manager.hpp"
# include "ControlsInclude.hpp"

struct PauseMenu : public UI::Control::Form
{
	UI::Control::Button		Continue;
	UI::Control::Button		Options;
	UI::Control::Button		Debug;
	UI::Control::Button		Exit;

	~PauseMenu();
	PauseMenu();
};

#endif