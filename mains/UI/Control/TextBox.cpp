#include "TextBox.hpp"
#include "OpenGL/openGL.h"



UI::Control::TextBox::TextBox(Manager & control_manager, UI::Text::Manager & text_manager)
	: Base(control_manager),
	TextManager(text_manager)
{
	Layer = 0.1f;
	Anchor.X.Anchor = ANCHOR_MIN;
	Anchor.Y.Anchor = ANCHOR_MIN;
	PixelMinDist = Point2D(12, 12);
	PixelSize = Point2D(50, 25);
	PixelMaxDist = Point2D(12, 12);
	NormalCenter = Point2D(0, 0);
	ColorDefault = Color(1.0f, 1.0f, 1.0f);
	ColorHover = Color(0.875f, 0.875f, 0.875f);
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
			Point2D min = PixelBox.Min;
			Point2D max = PixelBox.Max;
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
void UI::Control::TextBox::UpdateVisibilityRelay(bool make_visible)
{
	if (make_visible)
	{
		if (Visible == true && !TextEntry.Is())
		{
			TextEntry.Allocate(TextManager.Inst_Data_Container, 16);
			ChangedText = true;
		}
	}
	else
	{
		if (TextEntry.Is())
		{
			TextEntry.Dispose();
		}
	}
}
void UI::Control::TextBox::UpdateBoxRelay()
{
	if (TextEntry.Is())
	{
		Point2D PalletScale(25, 25);
		Point2D min = PixelBox.Min;
		Point2D max = PixelBox.Max;
		Point2D center = (max + min) / 2;
		for (unsigned int i = 0; i < TextEntry.Length(); i++)
		{
			TextEntry[i].Pos = Point2D((min.X + (PalletScale.X * 0.5f)) + (i * PalletScale.X), center.Y);
		}
	}
}



void UI::Control::TextBox::RelayKey(UI::Parameter::Key params)
{
	if (params.key == GLFW_KEY_BACKSPACE && (params.action == GLFW_PRESS || params.action == GLFW_REPEAT))
	{
		if (String.length() > 0)
		{
			String.erase(String.length() - 1, 1);
			ChangedText = true;
		}
	}
}
void UI::Control::TextBox::RelayText(UI::Parameter::Text params)
{
	if (
		(params.codepoint >= '0' && params.codepoint <= '9') ||
		(params.codepoint >= 'A' && params.codepoint <= 'Z') ||
		(params.codepoint >= 'a' && params.codepoint <= 'z') ||
		params.codepoint == '+' || params.codepoint == '-' || params.codepoint == '*' ||
		params.codepoint == '/' ||
		params.codepoint == '=' || params.codepoint == '<' || params.codepoint == '>' ||
		params.codepoint == ' '
		)
	{
		if (String.length() < TextEntry.Length())
		{
			String += (char)params.codepoint;
			ChangedText = true;
		}
	}
}
