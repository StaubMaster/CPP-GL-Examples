#ifndef  CONTEXT_1_MENU_HPP
# define CONTEXT_1_MENU_HPP

# include "ControlsInclude.hpp"

struct Context1Menu : public UI::Control::Form
{
	UI::Control::Button		QuitButton;
	UI::Control::TextBox	TitleText;

	UI::Control::Button		Context0Button;
	UI::Control::Button		Context1Button;
	UI::Control::TextBox	Text;

	UI::Control::GroupBox	SliderGroupBox;
	UI::Control::Slider		SliderHori;
	UI::Control::Slider		SliderVert;
	UI::Control::Slider		SliderArea;

	UI::Control::GroupBox	CheckGroupBox;
	UI::Control::CheckBox	Check0;
	UI::Control::CheckBox	Check1;
	UI::Control::CheckBox	Check2;
	UI::Control::CheckBox	Check3;

	~Context1Menu();
	Context1Menu();

	void	QuitFunc(ClickArgs args);
	void	Context0Func(ClickArgs args);
	void	Context1Func(ClickArgs args);

	void	SliderHoriChange(VectorF2 val);
	void	SliderVertChange(VectorF2 val);
	void	SliderAreaChange(VectorF2 val);
};

#endif