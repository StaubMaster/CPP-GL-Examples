#include "TextBox.hpp"
#include "Base/Manager.hpp"
#include <iostream>
#include <math.h>



UI::Control::TextBox::TextBox(UI::Text::Manager & text_manager)
	: Base(),
	TextManager(text_manager)
{
	Layer = 0.1f;
	Anchor.X.Anchor = ANCHOR_MIN;
	Anchor.Y.Anchor = ANCHOR_MIN;
	AnchorSize = Point2D(50, 25);
	ColorDefault = ColorF4(1.0f, 1.0f, 1.0f);
	ColorHover = ColorF4(0.875f, 0.875f, 0.875f);

	CharacterSize = Point2D(20, 20);
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
	if (CharacterCountLimit != count)
	{
		CharacterCountLimit = count;
		CharacterCountLimitChanged = true;
	}
}
void UI::Control::TextBox::PutCharactersEntrys()
{
	Point2D min = AnchorBox.Min;
	Point2D max = AnchorBox.Max;
	Point2D center = (max + min) / 2;
	for (unsigned int i = 0; i < TextEntry.Length(); i++)
	{
		TextEntry[i].Pos = Point2D((min.X + (CharacterSize.X * 0.5f)) + (i * CharacterSize.X), center.Y);
		if (i < Text.length())
		{ TextEntry[i].Pallet = TextManager.TextFont -> CharacterBoxFromCode(Text[i]); }
		else
		{ TextEntry[i].Pallet = TextManager.TextFont -> CharacterBoxFromCode('\0'); }
		TextEntry[i].Bound = AnchorBox;
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
			TextEntry.Dispose();
			TextManager.Inst_Data_Container.CompactHere();
			TextEntry.Allocate(TextManager.Inst_Data_Container, CharacterCountLimit);
			TextChanged = true;
			CharacterCountLimitChanged = false;
		}
		if (TextChanged)
		{
			PutCharactersEntrys();
			TextChanged = false;
		}
	}
}
void UI::Control::TextBox::InsertDrawingEntryRelay()
{
	if (!TextEntry.Is())
	{
		CalcCharacterCount();
		TextEntry.Allocate(TextManager.Inst_Data_Container, CharacterCountLimit);
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
		CalcCharacterCount();
		TextChanged = true;
	}
}



void UI::Control::TextBox::RelayKey(UserParameter::KeyBoard::Key params)
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
void UI::Control::TextBox::RelayText(UserParameter::KeyBoard::Text params)
{
	if (!Enabled || !Visible || !Drawable || ReadOnly) { return; }

	/*if (
		(params.Codepoint >= '0' && params.Codepoint <= '9') ||
		(params.Codepoint >= 'A' && params.Codepoint <= 'Z') ||
		(params.Codepoint >= 'a' && params.Codepoint <= 'z') ||
		params.Codepoint == '+' || params.Codepoint == '-' || params.Codepoint == '*' ||
		params.Codepoint == '/' ||
		params.Codepoint == '=' || params.Codepoint == '<' || params.Codepoint == '>' ||
		params.Codepoint == ' '
		)*/
	{
		Text += (char)params.Codepoint;
		TextChanged = true;
	}
}

