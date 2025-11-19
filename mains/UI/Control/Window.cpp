#include "Window.hpp"



Control::Window::Window(Manager & manager) : Base(manager)
{
	Layer = 1.0f;
	Anchor.X.Anchor = ANCHOR_BOTH;
	Anchor.Y.Anchor = ANCHOR_BOTH;
	PixelMinDist = Point2D(0, 0);
	PixelSize = Point2D(0, 0);
	PixelMaxDist = Point2D(0, 0);
	NormalCenter = Point2D(0, 0);
	ColorDefault = Color(0, 0, 0);
	ColorHover = Color(0, 0, 0);
}
Control::Window::~Window()
{ }
