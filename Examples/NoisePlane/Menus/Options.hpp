#ifndef  OPTIONS_MENU_HPP
# define OPTIONS_MENU_HPP

# include "Control/Base/Manager.hpp"
# include "ControlsInclude.hpp"

struct OptionsMenu : public UI::Control::Form
{
	UI::Control::TextBox	FOV_Name;
	UI::Control::Slider		FOV_Slider;
	UI::Control::TextBox	FOV_Value;

	UI::Control::TextBox	Chunk_Insert_Name;
	UI::Control::Slider		Chunk_Insert_Slider;
	UI::Control::TextBox	Chunk_Insert_Value;

	UI::Control::TextBox	Chunk_Remove_Name;
	UI::Control::Slider		Chunk_Remove_Slider;
	UI::Control::TextBox	Chunk_Remove_Value;

	UI::Control::Button		ButtonBack;

	~OptionsMenu();
	OptionsMenu();

	void	FOV_Change(float val);
	void	BackFunc(ClickArgs args);
};

#endif