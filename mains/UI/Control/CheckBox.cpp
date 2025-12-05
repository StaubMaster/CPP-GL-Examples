#include "CheckBox.hpp"
#include "Base/Manager.hpp"



UI::Control::CheckBox::CheckBox(Manager & manager) : Base(manager)
{
	Layer = 0.1f;
	Anchor.X.Anchor = ANCHOR_MIN;
	Anchor.Y.Anchor = ANCHOR_MIN;
	PixelSize = Point2D(25, 25);
	NormalCenter = Point2D(0, 0);
	ColorDefault = Color(1.0f, 0.0f, 0.0f);
	ColorHover = Color(0.75f, 0.0f, 0.0f);

	Checked = false;

	ColorChecked = Color(0.0f, 1.0f, 0.0f);
	ColorCheckedHover = Color(0.0f, 0.75f, 0.0f);
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
	if (ControlManager.Hovering != this)
	{
		if (Checked)
		{ (*Entry).Col = ColorDefault; }
		else
		{ (*Entry).Col = ColorChecked; }
	}
	else
	{
		if (Checked)
		{ (*Entry).Col = ColorHover; }
		else
		{ (*Entry).Col = ColorCheckedHover; }
	}
}
void UI::Control::CheckBox::RelayHover(unsigned char type)
{
	(void)type;
	ColorChanged = true;
}



void UI::Control::CheckBox::RelayClick(UI::Parameter::Click params)
{
	Checked = !Checked;
	ColorChanged = true;
	if (ClickFunc != NULL) { ClickFunc(params); }
}
