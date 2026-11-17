#include "ValueTypeUI/PropertyControl.hpp"



UI::Control_::PropertyControl::~PropertyControl()
{ }
UI::Control_::PropertyControl::PropertyControl(const char * name)
	: GroupBox()
	, Visible(true)
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



void UI::Control_::PropertyControl::ShowProperty()
{
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		if (Children[i] != &Toggle)
		{
			Children[i] -> Show();
		}
	}
	Visible = true;
	//AutoAnchorUpdateRequest();
	AutoAnchorUpdate();
	AutoFitMinY();
}
void UI::Control_::PropertyControl::HideProperty()
{
	for (unsigned int i = 0; i < Children.Count(); i++)
	{
		if (Children[i] != &Toggle)
		{
			Children[i] -> Hide();
		}
	}
	Visible = false;
	//AutoAnchorUpdateRequest();
	AutoAnchorUpdate();
	AutoFitMinY();
}

#include "User/MouseArgs.hpp"
void UI::Control_::PropertyControl::ToggleFunc(ClickArgs args)
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
