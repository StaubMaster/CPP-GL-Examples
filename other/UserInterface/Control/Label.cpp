#include "Label.hpp"
#include "General/Manager.hpp"
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



void UI::Control::Label::RelayUpdateBox()
{
	if (TextObject.Is())
	{
		PutCharactersEntrys();
	}
}

void UI::Control::Label::RelayInsertObject()
{
	if (!TextObject.Is() && Manager != NULL)
	{
		TextObject.Create();
	}
}
void UI::Control::Label::RelayRemoveObject()
{
	if (TextObject.Is() || Manager == NULL)
	{
		TextObject.Delete();
	}
}
