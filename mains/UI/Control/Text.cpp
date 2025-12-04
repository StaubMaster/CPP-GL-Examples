#include "Text.hpp"



UI::Control::Text::Text(Manager & manager) : Base(manager)
{
	Layer = 0.1f;
	Anchor.X.Anchor = ANCHOR_MIN;
	Anchor.Y.Anchor = ANCHOR_MIN;
	PixelMinDist = Point2D(12, 12);
	PixelSize = Point2D(120, 60);
	PixelMaxDist = Point2D(12, 12);
	NormalCenter = Point2D(0, 0);
	ColorDefault = Color(1.0f, 1.0f, 1.0f);
	ColorHover = Color(0.875f, 0.875f, 0.875f);
}
UI::Control::Text::~Text()
{ }
