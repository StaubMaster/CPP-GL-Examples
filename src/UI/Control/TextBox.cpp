#include "TextBox.hpp"
#include "OpenGL/openGL.h"
#include <iostream>



UI::Control::TextBox::TextBox(Manager & control_manager, UI::Text::Manager & text_manager)
	: Base(control_manager),
	TextManager(text_manager)
{
	Layer = 0.1f;
	Anchor.X.Anchor = ANCHOR_MIN;
	Anchor.Y.Anchor = ANCHOR_MIN;
	AnchorSize = Point2D(50, 25);
	ColorDefault = Color(1.0f, 1.0f, 1.0f);
	ColorHover = Color(0.875f, 0.875f, 0.875f);

	ReadOnly = false;
	SingleLine = true;
}
UI::Control::TextBox::~TextBox()
{ }





std::string UI::Control::TextBox::GetText() const
{
	return String;
}
void UI::Control::TextBox::SetText(std::string str)
{
	String = str;
	ChangedText = true;
}



void UI::Control::TextBox::UpdateEntrysRelay()
{
	if (TextEntry.Is())
	{
		if (ChangedText)
		{
			Point2D min = AnchorBox.Min;
			Point2D max = AnchorBox.Max;
			Point2D center = (max + min) / 2;
			for (unsigned int i = 0; i < TextEntry.Length(); i++)
			{
				if (i < String.length())
				{
					TextEntry[i].Pallet = UI::Text::Manager::CharToTextCoord(String[i]);
				}
				else
				{
					TextEntry[i].Pallet = UI::Text::Manager::CharToTextCoord('\0');
				}
			}
			ChangedText = false;
		}
	}
}
void UI::Control::TextBox::InsertDrawingEntryRelay()
{
	if (!TextEntry.Is())
	{
		TextEntry.Allocate(TextManager.Inst_Data_Container, 16);
		ChangedText = true;
	}
}
void UI::Control::TextBox::RemoveDrawingEntryRelay()
{
	if (TextEntry.Is())
	{
		TextEntry.Dispose();
	}
}

void UI::Control::TextBox::UpdateBoxRelay()
{
	if (TextEntry.Is())
	{
		Point2D PalletScale(25, 25);
		Point2D min = AnchorBox.Min;
		Point2D max = AnchorBox.Max;
		Point2D center = (max + min) / 2;
		for (unsigned int i = 0; i < TextEntry.Length(); i++)
		{
			TextEntry[i].Pos = Point2D((min.X + (PalletScale.X * 0.5f)) + (i * PalletScale.X), center.Y);
		}
	}
}



void UI::Control::TextBox::RelayKey(UserParameter::Key params)
{
	if (!Enabled || !Visible || !Drawable || ReadOnly) { return; }

	if (params.KeyCode == GLFW_KEY_BACKSPACE && (params.Action == GLFW_PRESS || params.Action == GLFW_REPEAT))
	{
		if (String.length() > 0)
		{
			String.erase(String.length() - 1, 1);
			ChangedText = true;
		}
	}
}
void UI::Control::TextBox::RelayText(UserParameter::Text params)
{
	if (!Enabled || !Visible || !Drawable || ReadOnly) { return; }

	if (
		(params.Codepoint >= '0' && params.Codepoint <= '9') ||
		(params.Codepoint >= 'A' && params.Codepoint <= 'Z') ||
		(params.Codepoint >= 'a' && params.Codepoint <= 'z') ||
		params.Codepoint == '+' || params.Codepoint == '-' || params.Codepoint == '*' ||
		params.Codepoint == '/' ||
		params.Codepoint == '=' || params.Codepoint == '<' || params.Codepoint == '>' ||
		params.Codepoint == ' '
		)
	{
		if (String.length() < TextEntry.Length())
		{
			String += (char)params.Codepoint;
			ChangedText = true;
		}
	}
}
