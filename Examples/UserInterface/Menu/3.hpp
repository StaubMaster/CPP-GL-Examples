#ifndef  USER_INTERFACE_MENU_3_HPP
# define USER_INTERFACE_MENU_3_HPP

# include "ControlsInclude.hpp"

struct UserInterfaceMenu3 : public UI::Control::Form
{
	UI::Control::Slider		Align;
	UI::Control::TextBox	Text;

	~UserInterfaceMenu3();
	UserInterfaceMenu3();

	void	AlignFunc(VectorF2 val);
};

#endif