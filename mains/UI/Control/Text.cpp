#include "Text.hpp"
#include "OpenGL/openGL.h"



UI::Control::Text::Text(Manager & control_manager, UI::Text::Manager & text_manager)
	: Base(control_manager),
	TextManager(text_manager)
{
	Layer = 0.1f;
	Anchor.X.Anchor = ANCHOR_MIN;
	Anchor.Y.Anchor = ANCHOR_MIN;
	PixelMinDist = Point2D(12, 12);
	PixelSize = Point2D(120, 60);
	PixelMaxDist = Point2D(12, 12);
	NormalCenter = Point2D(0, 0);
	ColorDefault = Color(1.0f, 1.0f, 1.0f);
	ColorHover = Color(0.875f, 0.875f, 0.875f);
}
UI::Control::Text::~Text()
{ }





std::string UI::Control::Text::GetText() const
{
	return String;
}
void UI::Control::Text::SetText(std::string str)
{
	String = str;
	ChangedText = true;
}



void UI::Control::Text::UpdateEntrysRelay()
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
void UI::Control::Text::UpdateVisibilityRelay(bool make_visible)
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
void UI::Control::Text::UpdateBoxRelay()
{
	if (TextEntry.Is())
	{
		Point2D min = PixelBox.Min;
		Point2D max = PixelBox.Max;
		Point2D center = (max + min) / 2;
		for (unsigned int i = 0; i < TextEntry.Length(); i++)
		{
			TextEntry[i].Pos = Point2D((min.X + 25) + (i * 50), center.Y);
		}
	}
}



void UI::Control::Text::Key(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_BACKSPACE && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (String.length() > 0)
		{
			String.erase(String.length() - 1, 1);
			ChangedText = true;
		}
	}
	(void)key;
	(void)scancode;
	(void)action;
	(void)mods;
}
void UI::Control::Text::DoText(unsigned int codepoint)
{
	if (
		(codepoint >= '0' && codepoint <= '9') ||
		(codepoint >= 'A' && codepoint <= 'Z') ||
		(codepoint >= 'a' && codepoint <= 'z') ||
		codepoint == '+' || codepoint == '-' || codepoint == '*' ||
		codepoint == '/' ||
		codepoint == '=' || codepoint == '<' || codepoint == '>' ||
		codepoint == ' '
		)
	{
		String += (char)codepoint;
		ChangedText = true;
	}
}