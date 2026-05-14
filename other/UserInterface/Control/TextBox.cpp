#include "TextBox.hpp"
#include "Base/Manager.hpp"
#include "Text/Manager.hpp"
#include <math.h>



UI::Control::TextBox::TextBox()
{
	Depth = 0.1f;
	Anchor.X.Anchor = AnchorType::Min;
	Anchor.Y.Anchor = AnchorType::Min;
	AnchorSize = VectorF2(50, 25);

	float padding = 0;
	AnchorPadding = BoxF2(VectorF2(padding, padding), VectorF2(padding, padding));

	ColorDefault = ColorF4(1.0f, 1.0f, 1.0f);
	ColorHover = ColorF4(0.875f, 0.875f, 0.875f);

	Text = "";

	ReadOnly = false;
	MultiLine = false;
}
UI::Control::TextBox::~TextBox() { }



void UI::Control::TextBox::PutCharactersEntrys()
{
	if (TextObject.Is())
	{
		TextObject.String() = Text;
		TextObject.TextPosition() = ContainerBox.Min;
		TextObject.AlignTopLeft();
		TextObject.Bound() = ContainerBox;
	}
}



std::string UI::Control::TextBox::GetText() const
{
	return Text;
}
void UI::Control::TextBox::SetText(std::string text)
{
	Text = text;
	PutCharactersEntrys();
}



void UI::Control::TextBox::RelayUpdateBox()
{
	if (TextObject.Is())
	{
		PutCharactersEntrys();
	}
}

void UI::Control::TextBox::RelayInsertObject()
{
	if (!TextObject.Is() && TextManager != NULL)
	{
		TextObject.Create();
	}
}
void UI::Control::TextBox::RelayRemoveObject()
{
	if (TextObject.Is() || TextManager == NULL)
	{
		TextObject.Delete();
	}
}



void UI::Control::TextBox::RelayKey(KeyArgs params)
{
	if (!IsInteractible() || ReadOnly) { return; }

	if ((params.Action == Action::Press || params.Action == Action::Repeat))
	{
		if (params.Key == Keys::Backspace)
		{
			if (Text.length() > 0)
			{
				Text.erase(Text.length() - 1, 1);
				PutCharactersEntrys();
			}
		}
		if (params.Key == Keys::Enter)
		{
			Text += '\n';
			PutCharactersEntrys();
		}
	}
}
void UI::Control::TextBox::RelayText(TextArgs params)
{
	if (!IsInteractible() || ReadOnly) { return; }

	Text += (char)params.Codepoint;
	PutCharactersEntrys();
}

