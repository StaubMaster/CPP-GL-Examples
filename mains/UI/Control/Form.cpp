#include "Form.hpp"



Control::Form::Form(Manager & manager) : Base(manager)
{
	Layer = 0.9f;
	Anchor.X.Anchor = ANCHOR_NONE;
	Anchor.Y.Anchor = ANCHOR_NONE;
	PixelMinDist = Point2D(12, 12);
	PixelSize = Point2D(480, 360);
	PixelMaxDist = Point2D(12, 12);
	NormalCenter = Point2D(0.5, 0.5);
	ColorDefault = Color(0.75f, 0.75f, 0.75f);
	ColorHover = Color(0.75f, 0.75f, 0.75f);
}
Control::Form::~Form()
{ }
