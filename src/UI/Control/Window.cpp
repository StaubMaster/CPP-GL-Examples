#include "Window.hpp"



UI::Control::Window::Window() : Base()
{
	Layer = 1.0f;
	Anchor.X.Anchor = AnchorType::Both;
	Anchor.Y.Anchor = AnchorType::Both;
	AnchorDist.Min = Point2D(0, 0);
	AnchorDist.Max = Point2D(0, 0);
	ColorDefault = ColorF4(0, 0, 0);
	ColorHover = ColorF4(0, 0, 0);
}
UI::Control::Window::~Window()
{ }



void UI::Control::Window::UpdateWindowSize(Point2D size)
{
	AnchorBox.Min = Point2D();
	AnchorBox.Max = size;
	UpdateBox();
}



void UI::Control::Window::ChangeManager(Manager * manager)
{
	ControlManager = manager;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> ChangeManager(manager);
	}
}
void UI::Control::Window::ChangeManager(UI::Text::Manager * manager)
{
	TextManager = manager;
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> ChangeManager(manager);
	}
}
