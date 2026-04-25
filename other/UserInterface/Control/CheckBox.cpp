#include "CheckBox.hpp"
#include "Base/Manager.hpp"

#include "User/MouseArgs.hpp"



UI::Control::CheckBox::CheckBox() : Base()
{
	Layer = 0.1f;
	Anchor.X.Anchor = AnchorType::Min;
	Anchor.Y.Anchor = AnchorType::Min;
	AnchorSize = Point2D(25, 25);
	ColorDefault = ColorF4(1.0f, 0.0f, 0.0f);
	ColorHover = ColorF4(0.75f, 0.0f, 0.0f);

	Checked = false;

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
	Color2Changed = true;
}
void UI::Control::CheckBox::Check(bool state)
{
	Checked = state;
	Color2Changed = true;
}



void UI::Control::CheckBox::UpdateEntryColorRelay()
{
	if (ControlManager -> Hovering != this)
	{
		if (!Checked)
		{ ControlObject.Color() = ColorDefault; }
		else
		{ ControlObject.Color() = ColorChecked; }
	}
	else
	{
		if (!Checked)
		{ ControlObject.Color() = ColorHover; }
		else
		{ ControlObject.Color() = ColorCheckedHover; }
	}
}
void UI::Control::CheckBox::RelayHover(unsigned char type)
{
	(void)type;
	ColorChanged = true;
}



void UI::Control::CheckBox::RelayClick(ClickArgs params)
{
	if (!_Interactible) { return; }

	//if (params.Action == Action::Press || params.Action == Action::Release)
	if (params.Action == Action::Press)
	{
		Checked = !Checked;
		ColorChanged = true;
		ClickFunc(params);
	}
}
