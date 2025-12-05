#include "Button.hpp"



UI::Control::Button::Button(Manager & manager) : Base(manager)
{
	Layer = 0.1f;
	Anchor.X.Anchor = ANCHOR_MIN;
	Anchor.Y.Anchor = ANCHOR_MIN;
	PixelMinDist = Point2D(12, 12);
	PixelSize = Point2D(75, 25);
	PixelMaxDist = Point2D(12, 12);
	NormalCenter = Point2D(0, 0);
	ColorDefault = Color(0.625f, 0.625f, 0.625f);
	ColorHover = Color(0.5f, 0.5f, 0.5f);
}
UI::Control::Button::~Button()
{ }



void UI::Control::Button::RelayClick(UI::Parameter::Click params)
{
	if (ClickFunc != NULL) { ClickFunc(params); }
}
