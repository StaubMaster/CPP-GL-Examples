#include "GroupBox.hpp"
#include "Base/Manager.hpp"
#include "UserParameter/MouseInclude.hpp"



UI::Control::GroupBox::GroupBox() : Base()
{
	Layer = 0.8f;
	Anchor.X.Anchor = AnchorType::None;
	Anchor.Y.Anchor = AnchorType::None;
	AnchorSize = Point2D(120, 120);
	ColorDefault = ColorF4(0.75f, 0.75f, 0.75f);
	ColorHover = ColorF4(0.75f, 0.75f, 0.75f);
}
UI::Control::GroupBox::~GroupBox()
{ }
