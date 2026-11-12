#include "Control/General/BaseText.hpp"
#include "Text/Manager.hpp"



UI::Control::BaseText::BaseText()
	: Base()
{
	float padding = 0;
	AnchorPadding = BoxF2(VectorF2(padding, padding), VectorF2(padding, padding));

	TextObjectData.Display = true;

	AlignmentX = UI::Text::Alignment::Min;
	AlignmentY = UI::Text::Alignment::Min;
	AlignmentUpdateFlag = true;
}



const std::string & UI::Control::BaseText::GetText() const
{
	return TextObjectData.Text;
}
void UI::Control::BaseText::SetText(const std::string & text)
{
	TextObjectData.Text = text;
}



void UI::Control::BaseText::AlignmentChangeX(UI::Text::Alignment alignment)
{
	AlignmentX = alignment;
	AlignmentUpdateRequest();
}
void UI::Control::BaseText::AlignmentChangeY(UI::Text::Alignment alignment)
{
	AlignmentY = alignment;
	AlignmentUpdateRequest();
}
void UI::Control::BaseText::AlignmentUpdateRequest()
{
	AlignmentUpdateFlag = true;
}
/*void UI::Control::BaseText::AlignmentUpdateResolve()
{
	if (AlignmentUpdateFlag)
	{
		AlignmentUpdate();
	}
}*/
void UI::Control::BaseText::AlignmentUpdate()
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



void UI::Control::BaseText::AnchorUpdate()
{
	Base::AnchorUpdate();

	AlignmentUpdateRequest();

	if (Parent != nullptr)
	{
		TextObjectData.Bound = Parent -> BoxBoarder().InnerBox(BoxContent());
	}
	else
	{
		TextObjectData.Bound = BoxContent();
	}
}

void UI::Control::BaseText::Update()
{
	Base::Update();

	//AlignmentUpdateResolve();
	if (AlignmentUpdateFlag) { AlignmentUpdate(); }

	TextObjectData.Depth = Depth(1.0f / 2.0f);
}



#include "UIManager.hpp"
void UI::Control::BaseText::DisplayPut() const
{
	Base::DisplayPut();
	if (_Manager() != nullptr && TextObjectData.Display)
	{
		_Manager() -> TextManager.InstancesPut(TextObjectData);
	}
}
