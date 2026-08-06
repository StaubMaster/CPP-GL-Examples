#include "BaseText.hpp"
#include "Text/Manager.hpp"



UI::Control::BaseText::~BaseText()
{ }
UI::Control::BaseText::BaseText()
	: Base()
	, Text()
	, TextObject()
	, TextObjectNewText(false)
	, TextObjectNewBound(false)
{
	float padding = 0;
	AnchorPadding = BoxF2(VectorF2(padding, padding), VectorF2(padding, padding));
}



std::string UI::Control::BaseText::GetText() const
{
	return Text;
}
void UI::Control::BaseText::SetText(std::string text)
{
	Text = text;
	TextObjectNewText = true;
	TextObjectAssign();
}



void UI::Control::BaseText::TextObjectAssign()
{
	if (TextObject.Is())
	{
		if (TextObjectNewText)
		{
			TextObjectAssignText();
			TextObjectNewText = false;
		}
		if (TextObjectNewBound)
		{
			TextObjectAssignBound();
			TextObjectNewBound = false;
		}
	}
}
void UI::Control::BaseText::TextObjectAssignText()
{
	TextObject.Text() = Text;
}
void UI::Control::BaseText::TextObjectAssignBound()
{
	TextObject.TextPosition() = BoxContent.Center();
	TextObject.Bound() = BoxContent;
}



void UI::Control::BaseText::RelayBoxUpdate()
{
	TextObjectNewBound = true;
	TextObjectAssign();
}

// is Checking Manager needed ?
void UI::Control::BaseText::RelayObjectInsert()
{
	if (!TextObject.Is() && Manager != nullptr)
	{
		TextObject.Create();

		TextObject.TextAlignmentX() = Text::Alignment::Mid;
		TextObject.TextAlignmentY() = Text::Alignment::Mid;
		TextObject.CharacterAlignmentX() = Text::Alignment::Mid;
		TextObject.CharacterAlignmentY() = Text::Alignment::Mid;

		TextObjectNewText = true;
		TextObjectNewBound = true;
	}
}
void UI::Control::BaseText::RelayObjectRemove()
{
	if (TextObject.Is() || Manager == nullptr)
	{
		TextObject.Delete();
	}
}
