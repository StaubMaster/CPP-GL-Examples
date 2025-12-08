#include "Window.hpp"



UI::Control::Window::Window(Manager & manager) : Base(manager)
{
	Layer = 1.0f;
	Anchor.X.Anchor = ANCHOR_BOTH;
	Anchor.Y.Anchor = ANCHOR_BOTH;
	AnchorDist.Min = Point2D(0, 0);
	AnchorDist.Max = Point2D(0, 0);
	ColorDefault = Color(0, 0, 0);
	ColorHover = Color(0, 0, 0);
}
UI::Control::Window::~Window()
{ }
