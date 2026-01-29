#include "Button.hpp"
#include "UserParameter/MouseInclude.hpp"



UI::Control::Button::Button() : Base()
{
	Layer = 0.1f;
	Anchor.X.Anchor = AnchorType::Min;
	Anchor.Y.Anchor = AnchorType::Min;
	AnchorSize = Point2D(75, 25);
	ColorDefault = ColorF4(0.625f, 0.625f, 0.625f);
	ColorHover = ColorF4(0.5f, 0.5f, 0.5f);

	ClickFunc = NULL;
}
UI::Control::Button::~Button()
{ }



void UI::Control::Button::RelayClick(UserParameter::Mouse::Click params)
{
	if (!_Interactible) { return; }

	ClickFunc(params);
}
