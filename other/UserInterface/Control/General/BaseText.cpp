#include "Control/General/BaseText.hpp"
#include "Text/Manager.hpp"



UI::Control_::BaseText::BaseText()
	: Control()
{
	float padding = 0;
	AnchorPadding = BoxF2(VectorF2(padding, padding), VectorF2(padding, padding));

	TextObjectData.Display = true;

	AlignmentX = UI::Text::Alignment::Min;
	AlignmentY = UI::Text::Alignment::Min;
	AlignmentUpdateFlag = true;
}



const std::string & UI::Control_::BaseText::GetText() const
{
	return TextObjectData.Text;
}
void UI::Control_::BaseText::SetText(const std::string & text)
{
	TextObjectData.Text = text;
}



void UI::Control_::BaseText::AlignmentChangeX(UI::Text::Alignment alignment)
{
	AlignmentX = alignment;
	AlignmentUpdateRequest();
}
void UI::Control_::BaseText::AlignmentChangeY(UI::Text::Alignment alignment)
{
	AlignmentY = alignment;
	AlignmentUpdateRequest();
}
void UI::Control_::BaseText::AlignmentUpdateRequest()
{
	AlignmentUpdateFlag = true;
}
/*void UI::Control_::BaseText::AlignmentUpdateResolve()
{
	if (AlignmentUpdateFlag)
	{
		AlignmentUpdate();
	}
}*/
void UI::Control_::BaseText::AlignmentUpdate()
{
	TextObjectData.TextAlignmentX = AlignmentX;
	TextObjectData.TextAlignmentY = AlignmentY;

	TextObjectData.CharacterAlignmentX = AlignmentX;
	TextObjectData.CharacterAlignmentY = AlignmentY;

	VectorF2 & pos = TextObjectData.TextPosition;

	if (AlignmentX == UI::Text::Alignment::Min) { pos.X = BoxContent().Min.X; }
	if (AlignmentX == UI::Text::Alignment::Mid) { pos.X = BoxContent().Center().X; }
	if (AlignmentX == UI::Text::Alignment::Max) { pos.X = BoxContent().Max.X; }

	if (AlignmentY == UI::Text::Alignment::Min) { pos.Y = BoxContent().Min.Y; }
	if (AlignmentY == UI::Text::Alignment::Mid) { pos.Y = BoxContent().Center().Y; }
	if (AlignmentY == UI::Text::Alignment::Max) { pos.Y = BoxContent().Max.Y; }

	AlignmentUpdateFlag = false;
}



void UI::Control_::BaseText::AnchorUpdate()
{
	Control::AnchorUpdate();

	AlignmentUpdateRequest();

	//if (Parent_ != nullptr)
	if (MetaIs())
	{
		//TextObjectData.Bound = Parent_ -> BoxBoarder().InnerBox(BoxContent());
		TextObjectData.Bound = MetaBoxBoarder().InnerBox(BoxContent());
	}
	else
	{
		TextObjectData.Bound = BoxContent();
	}
}

void UI::Control_::BaseText::Update()
{
	Control::Update();

	//AlignmentUpdateResolve();
	if (AlignmentUpdateFlag) { AlignmentUpdate(); }

	TextObjectData.Depth = -Depth(1.0f / 2.0f);
}



#include "UIManager.hpp"
void UI::Control_::BaseText::DisplayPut() const
{
	Control::DisplayPut();
	if (_Manager() != nullptr && TextObjectData.Display)
	{
		_Manager() -> TextManager.InstancesPut(TextObjectData);
	}
}
