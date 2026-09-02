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
	/*if (Object.Is())
	{
		TextObject.Bound() = Object.Bound().InnerBox(BoxContent);
	}
	else
	{
		TextObject.Bound() = BoxContent;
	}*/
	//TextObject.Bound() = ObjectData.Bound.InnerBox(BoxContent);
	if (Parent != nullptr)
	{
		TextObject.Bound() = Parent -> BoxBoarder.InnerBox(BoxContent);
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
	/*if (Object.Is())
	{
		TextObject.Bound() = Object.Bound().InnerBox(BoxContent);
	}
	else
	{
		TextObject.Bound() = BoxContent;
	}*/
	//TextObject.Bound() = ObjectData.Bound.InnerBox(BoxContent);
	if (Parent != nullptr)
	{
		TextObject.Bound() = Parent -> BoxBoarder.InnerBox(BoxContent);
	}
	else
	{
		TextObject.Bound() = BoxContent;
	}
}



#include "Control/Window.hpp"
#include "Control/Form.hpp"
void UI::Control::BaseText::AssignDepth()
{
	Base::AssignDepth();

	if (Window == nullptr) { return; }
	if (Form == nullptr) { return; }

	float size = Window -> DepthSize;
	float offset = Form -> DepthOffset;
	float layer = Layer;

	if (TextObject.Is())
	{
		TextObject.Depth() = -(((layer + (1.0f / 2.0f)) * size) + offset);
	}
}



void UI::Control::BaseText::BoxUpdate()
{
	Base::BoxUpdate();
	TextObjectNewBound = true;
	TextObjectAssign();
}

// is Checking Manager needed ?
void UI::Control::BaseText::DisplayShow()
{
	Base::DisplayShow();
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
void UI::Control::BaseText::DisplayHide()
{
	Base::DisplayHide();
	if (TextObject.Is() || Manager == nullptr)
	{
		TextObject.Delete();
	}
}
