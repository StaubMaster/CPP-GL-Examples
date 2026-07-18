#include "Control/Window.hpp"



UI::Control::Window::Window()
{
	Depth = 1.0f;
	Anchor.X.Anchor = AnchorType::Both;
	Anchor.Y.Anchor = AnchorType::Both;
	AnchorDist.Min = VectorF2(0, 0);
	AnchorDist.Max = VectorF2(0, 0);
	ColorDefault = ColorF4(0, 0, 0);
	ColorHover = ColorF4(0, 0, 0);
	_Opaque = false;
}
UI::Control::Window::~Window()
{ }



void UI::Control::Window::UpdateWindowSize(VectorF2 size)
{
	DisplayBox = BoxF2(VectorF2(), size);
	ContainerBox = DisplayBox;
	BoxWantUpdate();
}
