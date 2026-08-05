#include "Control/Label.hpp"
#include "Control/General/Manager.hpp"

#include "Text/Manager.hpp"
#include <math.h>



UI::Control::Label::Label()
	: Base()
{
	Depth = 0.1f;
	Anchor.X.Anchor = AnchorType::Min;
	Anchor.Y.Anchor = AnchorType::Min;
	AnchorSize = VectorF2(50, 25);

	float padding = 0;
	AnchorPadding = BoxF2(VectorF2(padding, padding), VectorF2(padding, padding));

	ColorDefault = ColorF4(0.75f, 0.75f, 0.75f);
	ColorHover = ColorF4(0.75f, 0.75f, 0.75f);

	Text = "";
}
UI::Control::Label::~Label() { }



void UI::Control::Label::PutCharactersEntrys()
{
	if (TextObject.Is())
	{
		TextObject.Text() = Text;
		TextObject.TextPosition() = BoxContent.Min;
		TextObject.AlignTopLeft();
		TextObject.Bound() = BoxContent;
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



void UI::Control::Label::RelayBoxUpdate()
{
	if (TextObject.Is())
	{
		PutCharactersEntrys();
	}
}

void UI::Control::Label::RelayObjectInsert()
{
	if (!TextObject.Is() && Manager != NULL)
	{
		TextObject.Create();
	}
}
void UI::Control::Label::RelayObjectRemove()
{
	if (TextObject.Is() || Manager == NULL)
	{
		TextObject.Delete();
	}
}
