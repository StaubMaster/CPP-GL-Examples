#include "Control/General/BaseText.hpp"
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
	TextObjectAssignPosition();
	if (Object.Is())
	{
		TextObject.Bound() = Object.Bound().InnerBox(BoxContent);
	}
	else
	{
		TextObject.Bound() = BoxContent;
	}
}
void UI::Control::BaseText::TextObjectAssignPosition()
{
	// Middle
	TextObject.TextPosition() = BoxContent.Center();
<<<<<<<< HEAD:Examples/UserInterface/Control/General/BaseText.cpp
	if (Object.Is())
	{
		TextObject.Bound() = Object.Bound().InnerBox(BoxContent);
	}
	else
	{
		TextObject.Bound() = BoxContent;
	}
========
>>>>>>>> b2e64cb9bf03df4d428eb94929acdc70f3966638:other/UserInterface/Control/General/BaseText.cpp
}



void UI::Control::BaseText::RelayAssignDepth()
{
	if (TextObject.Is())
	{
		TextObject.Depth() = Depth - 0.001f;
	}
}



void UI::Control::BaseText::BoxUpdate()
{
	Base::BoxUpdate();
	TextObjectNewBound = true;
	TextObjectAssign();
}

// is Checking Manager needed ?
void UI::Control::BaseText::ObjectInsert()
{
	Base::ObjectInsert();
	if (!TextObject.Is() && Manager != nullptr)
	{
		TextObject.Create();

		// Middle
		TextObject.TextAlignmentX() = Text::Alignment::Mid;
		TextObject.TextAlignmentY() = Text::Alignment::Mid;
		TextObject.CharacterAlignmentX() = Text::Alignment::Mid;
		TextObject.CharacterAlignmentY() = Text::Alignment::Mid;

		TextObject.Depth() = Depth - 0.001f;

		TextObjectNewText = true;
		TextObjectNewBound = true;
	}
}
void UI::Control::BaseText::ObjectRemove()
{
	Base::ObjectRemove();
	if (TextObject.Is() || Manager == nullptr)
	{
		TextObject.Delete();
	}
}
