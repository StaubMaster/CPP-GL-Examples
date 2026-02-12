#include "Form.hpp"



UI::Control::Form::Form() : Base()
{
	Layer = 0.9f;
	Anchor.X.Anchor = AnchorType::None;
	Anchor.Y.Anchor = AnchorType::None;
	AnchorSize = Point2D(480, 360);
	AnchorNormal = Point2D(0.5, 0.5);
	ColorDefault = ColorF4(0.75f, 0.75f, 0.75f);
	ColorHover = ColorF4(0.75f, 0.75f, 0.75f);
}
UI::Control::Form::~Form()
{ }
