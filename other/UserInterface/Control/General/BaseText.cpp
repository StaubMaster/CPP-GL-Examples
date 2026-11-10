#include "Control/General/BaseText.hpp"
#include "Text/Manager.hpp"



UI::Control::BaseText::BaseText()
	: Base()
{
	float padding = 0;
	AnchorPadding = BoxF2(VectorF2(padding, padding), VectorF2(padding, padding));

	TextObjectData.AlignMiddleMiddle();
	TextObjectData.Depth = Depth() - 0.001f;

	AlignmentX = UI::Text::Alignment::Min;
	AlignmentY = UI::Text::Alignment::Min;
	AlignmentUpdateFlag = true;
}



std::string UI::Control::BaseText::GetText() const
{
	return TextObjectData.Text;
}
void UI::Control::BaseText::SetText(std::string text)
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
void UI::Control::BaseText::AlignmentUpdateResolve()
{
	if (AlignmentUpdateFlag)
	{
		AlignmentUpdate();
	}
}
void UI::Control::BaseText::AlignmentUpdate()
{
	TextObjectData.TextAlignmentX = AlignmentX;
	TextObjectData.TextAlignmentY = AlignmentY;

	TextObjectData.CharacterAlignmentX = AlignmentX;
	TextObjectData.CharacterAlignmentY = AlignmentY;

	AlignmentUpdateFlag = false;
}



#include "Control/Window.hpp"
#include "Control/Form.hpp"
/*void UI::Control::BaseText::DepthUpdate()
{
	Base::DepthUpdate();

	if (Window == nullptr) { return; }
	if (Form == nullptr) { return; }

	float size = Window -> DepthSize;
	float offset = Form -> DepthOffset;
	float layer = Layer();

	TextObjectData.Depth = -(((layer + (1.0f / 2.0f)) * size) + offset);
}*/

void UI::Control::BaseText::BoxUpdate()
{
	Base::BoxUpdate();

	VectorF2 & pos = TextObjectData.TextPosition;

	if (AlignmentX == UI::Text::Alignment::Min) { pos.X = BoxContent.Min.X; }
	if (AlignmentX == UI::Text::Alignment::Mid) { pos.X = BoxContent.Center().X; }
	if (AlignmentX == UI::Text::Alignment::Max) { pos.X = BoxContent.Max.X; }

	if (AlignmentY == UI::Text::Alignment::Min) { pos.Y = BoxContent.Min.Y; }
	if (AlignmentY == UI::Text::Alignment::Mid) { pos.Y = BoxContent.Center().Y; }
	if (AlignmentY == UI::Text::Alignment::Max) { pos.Y = BoxContent.Max.Y; }

	if (Parent != nullptr)
	{
		TextObjectData.Bound = Parent -> BoxBoarder.InnerBox(BoxContent);
	}
	else
	{
		TextObjectData.Bound = BoxContent;
	}
}
void UI::Control::BaseText::Update()
{
	AlignmentUpdateResolve();
	Base::Update();
	if (Window != nullptr && Form != nullptr)
	{
		const float & size = Window -> DepthSize;
		const float & offset = Form -> DepthOffset;
		float layer = Layer();
		TextObjectData.Depth = -(((layer + (1.0f / 2.0f)) * size) + offset);
	}
}


#include "UIManager.hpp"
void UI::Control::BaseText::DisplayPut() const
{
	Base::DisplayPut();
	if (Manager != nullptr)
	{
		if (TextObjectData.Display) // should be checked in InstancePut ?
		{
			Manager -> TextManager.InstancesPut(TextObjectData);
		}
	}
}
void UI::Control::BaseText::DisplayShow()
{
	Base::DisplayShow();
	TextObjectData.Display = true;
}
void UI::Control::BaseText::DisplayHide()
{
	Base::DisplayHide();
	TextObjectData.Display = false;
}
