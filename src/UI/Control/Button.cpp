#include "Button.hpp"
#include "UserParameter/MouseInclude.hpp"



UI::Control::Button::Button() : Base()
{
	Layer = 0.1f;
	Anchor.X.Anchor = ANCHOR_MIN;
	Anchor.Y.Anchor = ANCHOR_MIN;
	AnchorSize = Point2D(75, 25);
	ColorDefault = ColorF4(0.625f, 0.625f, 0.625f);
	ColorHover = ColorF4(0.5f, 0.5f, 0.5f);
	
	ClickFunc = NULL;
}
UI::Control::Button::~Button()
{ }



void UI::Control::Button::RelayClick(UserParameter::Mouse::Click params)
{
	if (!Enabled || !Visible || !Drawable) { return; }

	if (ClickFunc != NULL) { ClickFunc(params); }
}
