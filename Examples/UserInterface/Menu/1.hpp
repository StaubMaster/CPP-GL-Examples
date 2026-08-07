#ifndef  USER_INTERFACE_MENU_1_HPP
# define USER_INTERFACE_MENU_1_HPP

# include "ControlsInclude.hpp"

struct UserInterfaceMenu1 : public UI::Control::Form
{
	UI::Control::GroupBox	SliderGroupBox;
	UI::Control::Slider		SliderHori;
	UI::Control::Slider		SliderVert;
	UI::Control::Slider		SliderArea;
	
	UI::Control::Graph		GraphHori;
	UI::Control::Graph		GraphVert;

	~UserInterfaceMenu1();
	UserInterfaceMenu1();

	void	SliderHoriChange(VectorF2 val);
	void	SliderVertChange(VectorF2 val);
	void	SliderAreaChange(VectorF2 val);
};

#endif