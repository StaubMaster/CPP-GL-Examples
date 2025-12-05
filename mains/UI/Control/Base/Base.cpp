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

	PixelMinDist = Point2D(12, 12);
	PixelMaxDist = Point2D(12, 12);
	PixelBoxChanged = false;

	ColorChanged = false;
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
		if (PixelBoxChanged)
		{
			UpdateEntryPixelBoxRelay();
			PixelBoxChanged = false;
		}
		if (ColorChanged)
		{
			UpdateEntryColorRelay();
			ColorChanged = false;
		}
	}
	UpdateEntrysRelay();
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> UpdateEntrys();
	}
}
void UI::Control::Base::UpdateEntryPixelBoxRelay()
{
	(*Entry).Min = PixelBox.Min;
	(*Entry).Max = PixelBox.Max;
	PixelBoxChanged = false;
}
void UI::Control::Base::UpdateEntryColorRelay()
{
	if (ControlManager.Hovering != this)
	{ (*Entry).Col = ColorDefault; }
	else
	{ (*Entry).Col = ColorHover; }
	ColorChanged = false;
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
			PixelBoxChanged = true;
			ColorChanged = true;
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
	PixelBoxChanged = true;
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

void UI::Control::Base::HoverEnter()
{
	ColorChanged = true;
	RelayHover(1);
}
void UI::Control::Base::HoverLeave()
{
	ColorChanged = true;
	RelayHover(0);
}
void UI::Control::Base::RelayHover(unsigned char type)
{
	(void)type;
}


void UI::Control::Base::RelayClick(UI::Parameter::Click params)
{
	(void)params;
}
void UI::Control::Base::RelayKey(UI::Parameter::Key params)
{
	(void)params;
}
void UI::Control::Base::RelayText(UI::Parameter::Text params)
{
	(void)params;
}
