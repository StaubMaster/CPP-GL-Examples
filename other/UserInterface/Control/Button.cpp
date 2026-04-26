#include "Button.hpp"
#include "User/MouseArgs.hpp"
#include "Text/Manager.hpp"
#include <math.h>



UI::Control::Button::Button() : Base()
{
	Layer = 0.1f;
	Anchor.X.Anchor = AnchorType::Min;
	Anchor.Y.Anchor = AnchorType::Min;
	AnchorSize = Point2D(75, 25);
	ColorDefault = ColorF4(0.625f, 0.625f, 0.625f);
	ColorHover = ColorF4(0.5f, 0.5f, 0.5f);

	CharacterCountLimit = 0;
	CharacterCountLimitChanged = false;

	Text = "";
	TextChanged = false;

	ClickFunc = nullptr;
}
UI::Control::Button::~Button()
{ }



void UI::Control::Button::CalcCharacterCount()
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
void UI::Control::Button::PutCharactersEntrys()
{
	Point2D min = AnchorBox.Min;
	Point2D max = AnchorBox.Max;
	Point2D center = (max + min) / 2.0f;

	if (TextObject.Is())
	{
		TextObject.String() = Text;
		TextObject.TextAlignmentX() = Text::Alignment::Mid;
		TextObject.TextAlignmentY() = Text::Alignment::Mid;
		TextObject.CharacterAlignmentX() = Text::Alignment::Mid;
		TextObject.CharacterAlignmentY() = Text::Alignment::Mid;
		TextObject.TextPosition() = center;
		TextObject.Bound() = AnchorBox;
	}
}



std::string UI::Control::Button::GetText() const
{
	return Text;
}
void UI::Control::Button::SetText(std::string text)
{
	Text = text;
	TextChanged = true;
}



void UI::Control::Button::UpdateEntrysRelay()
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
void UI::Control::Button::InsertDrawingEntryRelay()
{
	if (!TextObject.Is() && TextManager != NULL)
	{
		CalcCharacterCount();
		TextObject.Create();
		//TextEntry.Allocate(TextManager -> Inst_Data_Container, CharacterCountLimit);
	}
}
void UI::Control::Button::RemoveDrawingEntryRelay()
{
	if (TextObject.Is() || TextManager == NULL)
	{
		TextObject.Delete();
	}
}

void UI::Control::Button::UpdateBoxRelay()
{
	if (TextObject.Is())
	{
		CalcCharacterCount();
		TextChanged = true;
	}
}



void UI::Control::Button::RelayClick(ClickArgs params)
{
	if (!Interactible()) { return; }

	ClickFunc(params);
}
