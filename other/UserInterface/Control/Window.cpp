#include "Window.hpp"



UI::Control::Window::Window() : Base()
{
	Layer = 1.0f;
	Anchor.X.Anchor = AnchorType::Both;
	Anchor.Y.Anchor = AnchorType::Both;
	AnchorDist.Min = VectorF2(0, 0);
	AnchorDist.Max = VectorF2(0, 0);
	ColorDefault = ColorF4(0, 0, 0);
	ColorHover = ColorF4(0, 0, 0);
}
UI::Control::Window::~Window()
{ }



void UI::Control::Window::UpdateWindowSize(VectorF2 size)
{
	//AnchorBox.Min = VectorF2();
	//AnchorBox.Max = size;
	DisplayBox = BoxF2(VectorF2(), size);
	ContainerBox = DisplayBox;
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
