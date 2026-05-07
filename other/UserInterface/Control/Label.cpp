#include "Label.hpp"
#include "Base/Manager.hpp"
#include "Text/Manager.hpp"
#include <math.h>



UI::Control::Label::Label()
	: Base()
{
	Layer = 0.1f;
	Anchor.X.Anchor = AnchorType::Min;
	Anchor.Y.Anchor = AnchorType::Min;
	AnchorSize = Point2D(50, 25);

	float padding = 0;
	AnchorPadding = AxisBox2D(Point2D(padding, padding), Point2D(padding, padding));

	ColorDefault = ColorF4(0.75f, 0.75f, 0.75f);
	ColorHover = ColorF4(0.75f, 0.75f, 0.75f);

	Text = "";
}
UI::Control::Label::~Label() { }



void UI::Control::Label::PutCharactersEntrys()
{
	if (TextObject.Is())
	{
		TextObject.String() = Text;
		TextObject.TextPosition() = ContainerBox.Min;
		TextObject.AlignTopLeft();
		TextObject.Bound() = ContainerBox;
	}
}



std::string UI::Control::Label::GetText() const
{
	return Text;
}
void UI::Control::Label::SetText(std::string text)
{
	Text = text;
	PutCharactersEntrys();
}



void UI::Control::Label::InsertDrawingEntryRelay()
{
	if (!TextObject.Is() && TextManager != NULL)
	{
		TextObject.Create();
	}
}
void UI::Control::Label::RemoveDrawingEntryRelay()
{
	if (TextObject.Is() || TextManager == NULL)
	{
		TextObject.Delete();
	}
}

void UI::Control::Label::UpdateBoxRelay()
{
	if (TextObject.Is())
	{
		PutCharactersEntrys();
	}
}
