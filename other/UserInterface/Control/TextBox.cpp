#include "TextBox.hpp"
#include "Base/Manager.hpp"
#include "Text/Manager.hpp"
#include <math.h>



UI::Control::TextBox::TextBox()
	: Base()
{
	Layer = 0.1f;
	Anchor.X.Anchor = AnchorType::Min;
	Anchor.Y.Anchor = AnchorType::Min;
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

	if (TextObject.Is())
	{
		TextObject.String() = Text;
		TextObject.Pos().X = min.X + ((max.Y - min.Y) * 0.5f);
		TextObject.Pos().Y = center.Y;
		TextObject.Bound() = AnchorBox;
	}

	/*for (unsigned int i = 0; i < TextEntry.Length(); i++)
	{
		TextEntry[i].Pos = Point2D((min.X + (CharacterSize.X * 0.5f)) + (i * CharacterSize.X), center.Y);
		if (TextManager != NULL)
		{
			if (i < Text.length())
			{ TextEntry[i].Pallet = TextManager -> TextFont -> CharacterBoxFromCode(Text[i]); }
			else
			{ TextEntry[i].Pallet = TextManager -> TextFont -> CharacterBoxFromCode('\0'); }
		}
		TextEntry[i].Bound = AnchorBox;
	}*/
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
	if (TextObject.Is() && TextManager != NULL)
	{
		if (CharacterCountLimitChanged)
		{
			//TextObject.Delete();
			////TextManager -> Inst_Data_Container.CompactHere();
			////TextEntry.Allocate(TextManager -> Inst_Data_Container, CharacterCountLimit);
			//TextObject.Create();

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
	if (!TextObject.Is() && TextManager != NULL)
	{
		CalcCharacterCount();
		TextObject.Create();
		//TextEntry.Allocate(TextManager -> Inst_Data_Container, CharacterCountLimit);
	}
}
void UI::Control::TextBox::RemoveDrawingEntryRelay()
{
	if (TextObject.Is() || TextManager == NULL)
	{
		TextObject.Delete();
	}
}

void UI::Control::TextBox::UpdateBoxRelay()
{
	if (TextObject.Is())
	{
		CalcCharacterCount();
		TextChanged = true;
	}
}



void UI::Control::TextBox::RelayKey(KeyArgs params)
{
	if (!_Interactible || ReadOnly) { return; }

	if (params.Key == Keys::Backspace && (params.Action == Action::Press || params.Action == Action::Repeat))
	{
		if (Text.length() > 0)
		{
			Text.erase(Text.length() - 1, 1);
			TextChanged = true;
		}
	}
}
void UI::Control::TextBox::RelayText(TextArgs params)
{
	if (!_Interactible || ReadOnly) { return; }

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

