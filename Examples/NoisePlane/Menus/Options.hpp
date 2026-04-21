#ifndef  OPTIONS_MENU_HPP
# define OPTIONS_MENU_HPP

# include "Control/Base/Manager.hpp"
# include "ControlsInclude.hpp"

struct OptionsMenu : public UI::Control::Form
{
	UI::Control::TextBox	FOV_Name;
	UI::Control::Slider		FOV_Slider;
	UI::Control::TextBox	FOV_Value;

	UI::Control::Button		ButtonBack;

	~OptionsMenu();
	OptionsMenu();

	void FOV_Change(float val);
};

#endif