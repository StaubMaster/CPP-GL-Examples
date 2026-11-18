#include "UI/NestedProperty.hpp"



UI::NestedProperty::NestedProperty(const char * name)
	: UI::Control_::GroupBox()
	, Toggle()
{
//	AutoAnchorYType = EAutoAnchorType::StackMinFit;
	AutoAnchorYType = EAutoAnchorType::StackMin;

	//Toggle.Anchor.X.AnchorBoth(0, 0);
	Toggle.Make_Anchor_X_Both(nullptr, nullptr);
	Toggle.SetText(name);
	Toggle.ClickFunc.Assign(this, &NestedProperty::ToggleFunc);
	ChildInsert(Toggle);
}



void UI::NestedProperty::Maximize()
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
void UI::NestedProperty::Minimize()
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
void UI::NestedProperty::ExpansionChanged()
{
	AutoAnchorUpdate();
	AutoFitMinY();
	NestedProperty * control = dynamic_cast<NestedProperty *>(Parent());
	if (control != nullptr)
	{
		control -> ExpansionChanged();
	}
}

#include "User/MouseArgs.hpp"
void UI::NestedProperty::ToggleFunc(ClickArgs args)
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
