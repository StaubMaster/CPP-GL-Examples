#include "Control/Controls/GroupBox.hpp"
#include "AnchorEnum.hpp"



UI::Control_::GroupBox::GroupBox()
	: Control()
{
	Anchor.X.Anchor = AnchorType::None;
	Anchor.Y.Anchor = AnchorType::None;
	AnchorSize = VectorF2(120, 120);
	ColorDefault = ColorF4(0.75f, 0.75f, 0.75f);
}
