#include "Control/General/Control_Container.hpp"
#include "Control/Control.hpp"



void UI::Control_Container::ChildClear()
{
	Children.Clear();
}
void UI::Control_Container::ChildRemove(Control & control)
{
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		if (Children[i] == &control)
		{
			Children.RemoveAt(i);
			i--;
		}
	}
	// if count becomes 0, update depth
	// child might have had more depth then other children
	// allways update depth ?
}
void UI::Control_Container::ChildInsert(Control & control)
{
	// if count was 0, update Depth
	// child might have had more depth then other children
	// allways update depth ?
	Children.Insert(&control);
}



void UI::Control_Container::ChildRemove(Control * control)
{
	if (control != nullptr)
	{
		ChildRemove(*control);
	}
}
void UI::Control_Container::ChildInsert(Control * control)
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
