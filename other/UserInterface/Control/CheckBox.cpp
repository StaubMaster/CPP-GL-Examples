#include "Control/CheckBox.hpp"
#include "UIManager.hpp"

#include "User/MouseArgs.hpp"



UI::Control::CheckBox::CheckBox() : Base()
{
	Depth = 0.1f;
	Anchor.X.Anchor = AnchorType::Min;
	Anchor.Y.Anchor = AnchorType::Min;
	AnchorSize = VectorF2(25, 25);

	Checked = false;

	ColorDefault = ColorF4(1.0f, 0.0f, 0.0f);
	ColorHover = ColorF4(0.75f, 0.0f, 0.0f);

	ColorChecked = ColorF4(0.0f, 1.0f, 0.0f);
	ColorCheckedHover = ColorF4(0.0f, 0.75f, 0.0f);
}
UI::Control::CheckBox::~CheckBox()
{ }



bool UI::Control::CheckBox::IsChecked()
{
	return Checked;
}
void UI::Control::CheckBox::Toggle()
{
	Checked = !Checked;
	ObjectNewColor = true;
}
void UI::Control::CheckBox::Check(bool state)
{
	Checked = state;
	ObjectNewColor = true;
}



void UI::Control::CheckBox::RelayObjectAssignColor()
{
	if (Manager -> Hovering != this)
	{
		if (!Checked)
		{
			Object.Color() = ColorDefault;
		}
		else
		{
			Object.Color() = ColorChecked;
		}
	}
	else
	{
		if (!Checked)
		{
			Object.Color() = ColorHover;
		}
		else
		{
			Object.Color() = ColorCheckedHover;
		}
	}
}
void UI::Control::CheckBox::RelayHover(HoverArgs args)
{
	(void)args;
	ObjectNewColor = true;
}



void UI::Control::CheckBox::RelayClick(ClickArgs params)
{
	if (!IsInteractible()) { return; }

	//if (params.Action == Action::Press || params.Action == Action::Release)
	if (params.Action == Action::Press)
	{
		Checked = !Checked;
		ObjectNewColor = true;
		ClickFunc.TryInvoke(params);
	}
}
