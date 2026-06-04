#include "CheckBox.hpp"
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
	ObjectColorNeedAssign = true;
}
void UI::Control::CheckBox::Check(bool state)
{
	Checked = state;
	ObjectColorNeedAssign = true;
}



void UI::Control::CheckBox::RelayAssignObjectColor()
{
	if (Manager -> Hovering != this)
	{
		if (!Checked)
		{
			ControlObject.Color() = ColorDefault;
		}
		else
		{
			ControlObject.Color() = ColorChecked;
		}
	}
	else
	{
		if (!Checked)
		{
			ControlObject.Color() = ColorHover;
		}
		else
		{
			ControlObject.Color() = ColorCheckedHover;
		}
	}
}
void UI::Control::CheckBox::RelayHover(HoverArgs args)
{
	(void)args;
	ObjectColorNeedAssign = true;
}



void UI::Control::CheckBox::RelayClick(ClickArgs params)
{
	if (!IsInteractible()) { return; }

	//if (params.Action == Action::Press || params.Action == Action::Release)
	if (params.Action == Action::Press)
	{
		Checked = !Checked;
		ObjectColorNeedAssign = true;
		ClickFunc(params);
	}
}
