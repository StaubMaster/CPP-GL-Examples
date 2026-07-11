#include "Control/GroupBox.hpp"



UI::Control::GroupBox::GroupBox() : Base()
{
	Depth = 0.8f;
	Anchor.X.Anchor = AnchorType::None;
	Anchor.Y.Anchor = AnchorType::None;
	AnchorSize = VectorF2(120, 120);
	ColorDefault = ColorF4(0.75f, 0.75f, 0.75f);
	ColorHover = ColorF4(0.75f, 0.75f, 0.75f);
}
UI::Control::GroupBox::~GroupBox()
{ }
