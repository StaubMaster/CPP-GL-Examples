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
	if (Visible == false)
	{
		Visible = true;
	}
	ShowEntry();
	UpdateEntryAll();
}
void Control::Base::Hide()
{
	if (Visible == true)
	{
		Visible = false;
	}
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
	if (Visible == true && Entry != NULL)
	{
		Entry -> Dispose();
		Entry = NULL;
	}
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		Children[i] -> HideEntry();
	}
}
void Control::Base::UpdateEntryAll()
{
	if (Entry != NULL)
	{
		(*Entry)[0].Min = Normal0ToNormal1(PixelToNormal0(PixelBox.Min, ControlManager.ViewPortSize));
		(*Entry)[0].Max = Normal0ToNormal1(PixelToNormal0(PixelBox.Max, ControlManager.ViewPortSize));
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
