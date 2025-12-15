#include "GroupBox.hpp"
#include "Base/Manager.hpp"
#include "UserParameter/MouseInclude.hpp"



UI::Control::GroupBox::GroupBox() : Base()
{
	Layer = 0.8f;
	Anchor.X.Anchor = ANCHOR_NONE;
	Anchor.Y.Anchor = ANCHOR_NONE;
	AnchorSize = Point2D(120, 120);
	ColorDefault = Color(0.75f, 0.75f, 0.75f);
	ColorHover = Color(0.75f, 0.75f, 0.75f);
}
UI::Control::GroupBox::~GroupBox()
{ }
