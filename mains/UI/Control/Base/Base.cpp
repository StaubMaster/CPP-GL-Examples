#include "Base.hpp"
#include "Manager.hpp"
#include <iostream>



UI::Control::Base::Base(Manager & manager) :
	ControlManager(manager),
	Entry(),
	Children(Container::IncreaseBehaviour::Binary, Container::DecreaseBehaviour::Binary)
{
	Visible = true;
	ClickFunc = NULL;
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

void UI::Control::Base::Show()
{

	Visible = true;
	ShowEntry();
	UpdateEntryAll();
}
void UI::Control::Base::Hide()
{
	Visible = false;
	HideEntry();
	UpdateEntryAll();
}

void UI::Control::Base::ShowEntry()
{
	//if (Visible == true && Entry == NULL)
	if (Visible == true && !Entry.Is())
	{
		//Entry = ControlManager.Inst_Data_Container.Alloc(1);
		Entry.Allocate(ControlManager.Inst_Data_Container, 1);
	}
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> ShowEntry();
	}
}
void UI::Control::Base::HideEntry()
{
	//if (Entry != NULL)
	if (Entry.Is())
	{
		//std::cout << "Count " << ControlManager.Inst_Data_Container.Limit() << "\n";
		//std::cout << "Count " << ControlManager.Inst_Data_Container.Count() << "\n";
		//std::cout << "Count " << ControlManager.Inst_Data_Container.Entrys.Count() << "\n";
		//Entry -> Dispose();
		Entry.Dispose();
		//Entry = NULL;
	}
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> HideEntry();
	}
}
void UI::Control::Base::UpdateEntryAll()
{
	//if (Entry != NULL)
	if (Entry.Is())
	{
		//(*Entry)[0].Min = PixelBox.Min;
		//(*Entry)[0].Max = PixelBox.Max;
		//(*Entry)[0].Layer = Layer;
		(*Entry).Min = PixelBox.Min;
		(*Entry).Max = PixelBox.Max;
		(*Entry).Layer = Layer;
		if (ControlManager.Hovering == this)
		{
			//(*Entry)[0].Col = ColorHover;
			(*Entry).Col = ColorHover;
		}
		else
		{
			//(*Entry)[0].Col = ColorDefault;
			(*Entry).Col = ColorDefault;
		}
	}
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> UpdateEntryAll();
	}
}

void UI::Control::Base::UpdateBox(const AxisBox2D & BaseBox)
{
	PixelBox = Anchor.Calculate(AxisBox2D(PixelMinDist, PixelMaxDist), PixelSize, NormalCenter, BaseBox);
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> UpdateBox(PixelBox);
	}
}
bool UI::Control::Base::UpdateHover(Point2D mouse)
{
	if (!Visible) { return false; }
	if (PixelBox.Intersekt(mouse))
	{
		ControlManager.ChangeHover(this);
		//unsigned int hover_idx = 0xFFFFFFFF;
		for (unsigned int i = 0; i < Children.Count(); i++)
		{
			if (Children[i] -> UpdateHover(mouse))
			{
			}
		}
		return true;
	}
	return false;
}
