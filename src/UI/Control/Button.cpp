#include "Button.hpp"



UI::Control::Button::Button(Manager & manager) : Base(manager)
{
	Layer = 0.1f;
	Anchor.X.Anchor = ANCHOR_MIN;
	Anchor.Y.Anchor = ANCHOR_MIN;
	AnchorSize = Point2D(75, 25);
	ColorDefault = Color(0.625f, 0.625f, 0.625f);
	ColorHover = Color(0.5f, 0.5f, 0.5f);
	
	ClickFunc = NULL;
}
UI::Control::Button::~Button()
{ }



void UI::Control::Button::RelayClick(UserParameter::Mouse::Click params)
{
	if (!Enabled || !Visible || !Drawable) { return; }

	if (ClickFunc != NULL) { ClickFunc(params); }
}
