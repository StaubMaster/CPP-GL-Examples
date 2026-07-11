#ifndef  PAUSE_MENU_HPP
# define PAUSE_MENU_HPP

# include "Control/General/Manager.hpp"
# include "ControlsInclude.hpp"

struct ContextNoisePlane;

struct PauseMenu : public UI::Control::Form
{
	ContextNoisePlane &		Context;

	UI::Control::Button		Continue;
	UI::Control::Button		Options;
	UI::Control::Button		Debug;
	UI::Control::Button		Exit;

	~PauseMenu();
	PauseMenu(ContextNoisePlane & context);

	void	ContinueFunc(ClickArgs args);
	void	OptionsFunc(ClickArgs args);
	void	DebugFunc(ClickArgs args);
	void	ExitFunc(ClickArgs args);
};

#endif