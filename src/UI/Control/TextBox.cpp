#include "TextBox.hpp"
#include "OpenGL/openGL.h"
#include <iostream>
#include <math.h>



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

	CharacterSize = Point2D(25, 25);
	CharacterCountLimit = 0;
	CharacterCountLimitChanged = false;

	Text = "";
	TextChanged = false;

	ReadOnly = false;
	SingleLine = true;

	CalcCharacterCount();
}
UI::Control::TextBox::~TextBox()
{ }



void UI::Control::TextBox::CalcCharacterCount()
{
	CharacterCountLimit2D = AnchorSize / CharacterSize;
	unsigned int count = 0;
	count += ceil(CharacterCountLimit2D.X);
	count += ceil(CharacterCountLimit2D.Y);
	std::cout << "new Count " << CharacterCountLimit << " " << count << "\n";
	if (CharacterCountLimit != count)
	{
		CharacterCountLimit = count;
		CharacterCountLimitChanged = true;
	}
}



std::string UI::Control::TextBox::GetText() const
{
	return Text;
}
void UI::Control::TextBox::SetText(std::string text)
{
	Text = text;
	TextChanged = true;
}



void UI::Control::TextBox::UpdateEntrysRelay()
{
	if (TextEntry.Is())
	{
		if (CharacterCountLimitChanged)
		{
			std::cout << "Update CharacterCountLimitChanged\n";
			TextEntry.Dispose();
			TextManager.Inst_Data_Container.CompactHere();
			TextEntry.Allocate(TextManager.Inst_Data_Container, CharacterCountLimit);
			TextChanged = true;
			CharacterCountLimitChanged = false;
		}
		if (TextChanged)
		{
			Point2D min = AnchorBox.Min;
			Point2D max = AnchorBox.Max;
			Point2D center = (max + min) / 2;
			for (unsigned int i = 0; i < TextEntry.Length(); i++)
			{
				if (i < Text.length())
				{
					TextEntry[i].Pallet = UI::Text::Manager::CharToTextCoord(Text[i]);
				}
				else
				{
					TextEntry[i].Pallet = UI::Text::Manager::CharToTextCoord('\0');
				}
			}
			TextChanged = false;
		}
	}
}
void UI::Control::TextBox::InsertDrawingEntryRelay()
{
	std::cout << "  Insert Text " << (TextEntry.Is()) << '\n';
	std::cout << "Size " << AnchorSize.X << " " << AnchorSize.Y << "\n";
	if (!TextEntry.Is())
	{
		CalcCharacterCount();
		TextEntry.Allocate(TextManager.Inst_Data_Container, CharacterCountLimit);
	}
	std::cout << "! Insert Text " << (TextEntry.Is()) << '\n';
}
void UI::Control::TextBox::RemoveDrawingEntryRelay()
{
	std::cout << "  Remove Text " << (TextEntry.Is()) << '\n';
	if (TextEntry.Is())
	{
		TextEntry.Dispose();
	}
	std::cout << "! Remove Text " << (TextEntry.Is()) << '\n';
}

void UI::Control::TextBox::UpdateBoxRelay()
{
	std::cout << "Update Text Box " << (TextEntry.Is()) << '\n';
	if (TextEntry.Is())
	{
		std::cout << "Size " << AnchorSize.X << " " << AnchorSize.Y << "\n";
		CalcCharacterCount();

		Point2D min = AnchorBox.Min;
		Point2D max = AnchorBox.Max;
		Point2D center = (max + min) / 2;
		for (unsigned int i = 0; i < TextEntry.Length(); i++)
		{
			TextEntry[i].Pos = Point2D((min.X + (CharacterSize.X * 0.5f)) + (i * CharacterSize.X), center.Y);
		}
	}
}



void UI::Control::TextBox::RelayClick(UserParameter::Click params)
{
	if (params.Code == GLFW_MOUSE_BUTTON_2 && params.Action.IsPress())
	{
		std::cout << "TextBox Info\n";
		std::cout << "Limit2D" << ' ' << CharacterCountLimit2D.X << ' ' << CharacterCountLimit2D.Y << '\n';
		std::cout << "Limit  " << ' ' << CharacterCountLimit << '\n';
		std::cout << "Entry  " << ' ' << TextEntry.Length() << '\n';
		std::cout << "Text   " << ' ' << '"' << Text << '"' << '\n';
	}
	if (params.Code == GLFW_MOUSE_BUTTON_3 && params.Action.IsPress())
	{
		TextChanged = true;
	}
}
void UI::Control::TextBox::RelayKey(UserParameter::Key params)
{
	if (!Enabled || !Visible || !Drawable || ReadOnly) { return; }

	if (params.Code == GLFW_KEY_BACKSPACE && (params.Action.IsPress() || params.Action.IsRepeat()))
	{
		if (Text.length() > 0)
		{
			Text.erase(Text.length() - 1, 1);
			TextChanged = true;
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
		Text += (char)params.Codepoint;
		TextChanged = true;
	}
}

