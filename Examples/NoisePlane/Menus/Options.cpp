#include "Options.hpp"



OptionsMenu::~OptionsMenu() { }
OptionsMenu::OptionsMenu()
	: UI::Control::Form()
{
	MakeTransparent();

	float x;
	x = 0.0f;

	FOV_Name.Anchor.X.AnchorMin(x, 100);
	FOV_Name.Anchor.Y.AnchorMin(0);
	FOV_Name.SetText("FOV");
	ChildInsert(FOV_Name);

	x = FOV_Name.Anchor.X.GetMinSize();

	FOV_Slider.Anchor.X.AnchorMin(x, 200);
	FOV_Slider.Anchor.Y.AnchorMin(0);
	FOV_Slider.ValueMin = 20;
	FOV_Slider.SetValue(90);
	FOV_Slider.ValueMax = 160;
	ChildInsert(FOV_Slider);

	x = FOV_Slider.Anchor.X.GetMinSize();

	FOV_Value.Anchor.X.AnchorMin(x, 100);
	FOV_Value.Anchor.Y.AnchorMin(0);
	FOV_Value.SetText(std::to_string(90));
	ChildInsert(FOV_Value);

	ButtonBack.Anchor.X.AnchorMin(0);
	ButtonBack.Anchor.Y.AnchorMax(0);
	ChildInsert(ButtonBack);
}
