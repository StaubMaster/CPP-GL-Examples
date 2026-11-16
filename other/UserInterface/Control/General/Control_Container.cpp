#include "Control_Container.hpp"
#include "Control_Base.hpp"



void UI::Control_Container::ChildClear()
{
	Children.Clear();
}
void UI::Control_Container::ChildRemove(Control_Base & control)
{
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		if (Children[i] == &control)
		{
			Children.RemoveAt(i);
			i--;
		}
	}
}
void UI::Control_Container::ChildInsert(Control_Base & control)
{
	Children.Insert(&control);
}



void UI::Control_Container::ChildRemove(Control_Base * control)
{
	if (control != nullptr)
	{
		ChildRemove(*control);
	}
}
void UI::Control_Container::ChildInsert(Control_Base * control)
{
	if (control != nullptr)
	{
		ChildInsert(*control);
	}
}



/* Recursive : Hovering & Selected

UpdateHovering()
{
	control = FindHovering()

	if (control == Hovering)
	{
		Hovering.Relay(Move)
	}
	else
	{
		Hovering.Relay(Leave) recursive
		Hovering = control
		Hovering.Relay(Enter)
	}

	control.UpdateHovering()
}

*/
