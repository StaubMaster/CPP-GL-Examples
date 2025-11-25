#include "Base.hpp"
#include "Manager.hpp"



Control::Base::Base(Manager & manager) :
	ControlManager(manager)
{
	Entry = NULL,
	Visible = true;
	ClickFunc = NULL;
}
Control::Base::~Base()
{
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		delete Children[i];
	}
}

void Control::Base::Show()
{
	Visible = true;
	ShowEntry();
	UpdateEntryAll();
}
void Control::Base::Hide()
{
	Visible = false;
	HideEntry();
}

void Control::Base::ShowEntry()
{
	if (Visible == true && Entry == NULL)
	{
		Entry = ControlManager.Inst_Data_Container.Alloc(1);
	}
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> ShowEntry();
	}
}
void Control::Base::HideEntry()
{
	if (Entry != NULL)
	{
		std::cout << "Count " << ControlManager.Inst_Data_Container.Length << "\n";
		std::cout << "Count " << ControlManager.Inst_Data_Container.Size << "\n";
		std::cout << "Count " << ControlManager.Inst_Data_Container.EntryRefs.Count() << "\n";
		std::cout << "Dispose\n";
		Entry -> Dispose();
		std::cout << "Dispose\n";
		Entry = NULL;
	}
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		std::cout << "Here " << i << "\n";
		Children[i] -> HideEntry();
		std::cout << "Here " << i << "\n";
	}
}
void Control::Base::UpdateEntryAll()
{
	if (Entry != NULL)
	{
		(*Entry)[0].Min = PixelBox.Min;
		(*Entry)[0].Max = PixelBox.Max;
		(*Entry)[0].Layer = Layer;
		if (ControlManager.Hovering == this)
		{
			(*Entry)[0].Col = ColorHover;
		}
		else
		{
			(*Entry)[0].Col = ColorDefault;
		}
	}
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> UpdateEntryAll();
	}
}

void Control::Base::UpdateBox(const AxisBox2D & BaseBox)
{
	PixelBox = Anchor.Calculate(AxisBox2D(PixelMinDist, PixelMaxDist), PixelSize, NormalCenter, BaseBox);
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> UpdateBox(PixelBox);
	}
}
bool Control::Base::UpdateHover(Point2D mouse)
{
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
