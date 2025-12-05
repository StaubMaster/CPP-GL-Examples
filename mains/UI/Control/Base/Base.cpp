#include "Base.hpp"
#include "Manager.hpp"
#include <iostream>



UI::Control::Base::Base(Manager & manager) :
	ControlManager(manager),
	Entry(),
	Children()
{
	Visible = true;
	ClickFunc = NULL;
	ChangedBox = false;
	ChangedColor = false;
}
UI::Control::Base::~Base()
{
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		delete Children[i];
	}
}





void UI::Control::Base::Info(std::string padding) const
{
	std::cout << padding << "this " << this << '\n';
	std::cout << padding << "Entry " << Entry.Is() << '\n';
	std::cout << padding << "Children " << Children.Count() << '\n';
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> Info(padding + "  ");
	}
}



void UI::Control::Base::UpdateEntrys()
{
	if (Entry.Is())
	{
		if (ChangedBox)
		{
			(*Entry).Min = PixelBox.Min;
			(*Entry).Max = PixelBox.Max;
		}
		if (ChangedColor)
		{
			if (ControlManager.Hovering == this)
			{ (*Entry).Col = ColorHover; }
			else
			{ (*Entry).Col = ColorDefault; }
		}
	}
	UpdateEntrysRelay();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> UpdateEntrys();
	}
}
void UI::Control::Base::UpdateEntrysRelay()
{

}




void UI::Control::Base::Show()
{
	Visible = true;
	UpdateVisibility(true);
}
void UI::Control::Base::Hide()
{
	Visible = false;
	UpdateVisibility(false);
}

void UI::Control::Base::UpdateVisibility(bool make_visible)
{
	if (make_visible)
	{
		if (Visible == true && !Entry.Is())
		{
			Entry.Allocate(ControlManager.Inst_Data_Container, 1);
			(*Entry).Layer = Layer;
			ChangedBox = true;
			ChangedColor = true;
		}
	}
	else
	{
		if (Entry.Is())
		{
			Entry.Dispose();
		}
	}
	UpdateVisibilityRelay(make_visible);
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> UpdateVisibility(make_visible);
	}
}
void UI::Control::Base::UpdateVisibilityRelay(bool make_visible)
{
	(void)make_visible;
}





void UI::Control::Base::UpdateBox(const AxisBox2D & BaseBox)
{
	PixelBox = Anchor.Calculate(AxisBox2D(PixelMinDist, PixelMaxDist), PixelSize, NormalCenter, BaseBox);
	UpdateBoxRelay();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> UpdateBox(PixelBox);
	}
}
void UI::Control::Base::UpdateBoxRelay()
{

}


UI::Control::Base * UI::Control::Base::CheckHover(Point2D mouse)
{
	if (!Visible) { return NULL; }
	if (PixelBox.Intersekt(mouse))
	{
		Base * control = NULL;
		for (unsigned int i = 0; i < Children.Count(); i++)
		{
			Base * c = Children[i] -> CheckHover(mouse);
			if (c != NULL && (control == NULL || c -> Layer < control -> Layer))
			{
				control = c;
			}
		}
		if (control != NULL)
		{ return control; }
		return this;
	}
	return NULL;
}





void UI::Control::Base::Click(unsigned char code, unsigned char action)
{
	(void)code;
	(void)action;
}
void UI::Control::Base::Key(int key, int scancode, int action, int mods)
{
	(void)key;
	(void)scancode;
	(void)action;
	(void)mods;
}
void UI::Control::Base::DoText(unsigned int codepoint)
{
	(void)codepoint;
}
