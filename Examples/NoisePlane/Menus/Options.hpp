#ifndef  OPTIONS_MENU_HPP
# define OPTIONS_MENU_HPP

# include "Control/Base/Manager.hpp"
# include "ControlsInclude.hpp"

struct OptionsMenu : public UI::Control::Form
{
	UI::Control::Slider		FOV;
	UI::Control::Slider		Depth;
	UI::Control::Slider		ChunkInsert;
	UI::Control::Slider		ChunkRemove;
	UI::Control::Button		Back;

	~OptionsMenu();
	OptionsMenu();
};

#endif