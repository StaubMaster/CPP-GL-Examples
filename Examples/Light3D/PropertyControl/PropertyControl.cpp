#include "PropertyControl/PropertyControl.hpp"



UI::Control::PropertyControl::~PropertyControl()
{ }
UI::Control::PropertyControl::PropertyControl(const char * name)
	: GroupBox()
	, Visible(true)
	, Toggle()
{
	Toggle.Anchor.X.AnchorBoth(0, 0);
	Toggle.SetText(name);
	Toggle.ClickFunc.Assign(this, &PropertyControl::ToggleFunc);
	ChildInsert(Toggle);
}



void UI::Control::PropertyControl::ShowProperty()
{
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		if (Children[i] != &Toggle)
		{
			Children[i] -> Show();
		}
	}
	Visible = true;
	AnchorFitChildrenY();
}
void UI::Control::PropertyControl::HideProperty()
{
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		if (Children[i] != &Toggle)
		{
			Children[i] -> Hide();
		}
	}
	Visible = false;
	AnchorFitChildrenY();
}

void UI::Control::PropertyControl::ToggleFunc(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		if (Visible)
		{
			HideProperty();
		}
		else
		{
			ShowProperty();
		}
	}
}
