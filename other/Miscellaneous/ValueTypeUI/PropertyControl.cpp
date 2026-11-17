#include "ValueTypeUI/PropertyControl.hpp"



UI::Control_::PropertyControl::PropertyControl(const char * name)
	: GroupBox()
	, Toggle()
{
//	AutoAnchorYType = EAutoAnchorType::StackMinFit;
	AutoAnchorYType = EAutoAnchorType::StackMin;

	//Toggle.Anchor.X.AnchorBoth(0, 0);
	Toggle.Make_Anchor_X_Both(nullptr, nullptr);
	Toggle.SetText(name);
	Toggle.ClickFunc.Assign(this, &PropertyControl::ToggleFunc);
	ChildInsert(Toggle);
}



void UI::Control_::PropertyControl::Maximize()
{
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		if (Children[i] != &Toggle)
		{
			Children[i] -> Show();
		}
	}
	Expanded = true;
	ExpansionChanged();
}
void UI::Control_::PropertyControl::Minimize()
{
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		if (Children[i] != &Toggle)
		{
			Children[i] -> Hide();
		}
	}
	Expanded = false;
	ExpansionChanged();
}
void UI::Control_::PropertyControl::ExpansionChanged()
{
	AutoAnchorUpdate();
	AutoFitMinY();
	PropertyControl * control = dynamic_cast<PropertyControl *>(Parent());
	if (control != nullptr)
	{
		control -> ExpansionChanged();
	}
}

#include "User/MouseArgs.hpp"
void UI::Control_::PropertyControl::ToggleFunc(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		if (Expanded)
		{
			Minimize();
		}
		else
		{
			Maximize();
		}
	}
}
