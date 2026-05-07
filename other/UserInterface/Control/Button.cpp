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

	float padding = 0;
	AnchorPadding = AxisBox2D(Point2D(padding, padding), Point2D(padding, padding));

	ColorDefault = ColorF4(0.625f, 0.625f, 0.625f);
	ColorHover = ColorF4(0.5f, 0.5f, 0.5f);

	Text = "";

	ClickFunc = nullptr;
}
UI::Control::Button::~Button()
{ }



void UI::Control::Button::PutCharactersEntrys()
{
	if (TextObject.Is())
	{
		TextObject.String() = Text;
		TextObject.TextAlignmentX() = Text::Alignment::Mid;
		TextObject.TextAlignmentY() = Text::Alignment::Mid;
		TextObject.CharacterAlignmentX() = Text::Alignment::Mid;
		TextObject.CharacterAlignmentY() = Text::Alignment::Mid;
		TextObject.TextPosition() = ContainerBox.Center();
		TextObject.Bound() = ContainerBox;
	}
}



std::string UI::Control::Button::GetText() const
{
	return Text;
}
void UI::Control::Button::SetText(std::string text)
{
	Text = text;
	PutCharactersEntrys();
}



void UI::Control::Button::InsertDrawingEntryRelay()
{
	if (!TextObject.Is() && TextManager != NULL)
	{
		TextObject.Create();
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
		PutCharactersEntrys();
	}
}



void UI::Control::Button::RelayClick(ClickArgs params)
{
	if (!IsInteractible()) { return; }

	ClickFunc(params);
}
