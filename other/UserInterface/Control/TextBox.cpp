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
	TextCursor = 0;

	ReadOnly = false;
	MultiLine = false;

	AlignmentX = UI::Text::Alignment::Min;
	AlignmentY = UI::Text::Alignment::Min;
}
UI::Control::TextBox::~TextBox() { }



void UI::Control::TextBox::PutAlignment()
{
	if (TextObject.Is())
	{
		VectorF2 & pos = TextObject.TextPosition();

		if (AlignmentX == UI::Text::Alignment::Min) { pos.X = ContainerBox.Min.X; }
		if (AlignmentX == UI::Text::Alignment::Mid) { pos.X = ContainerBox.Center().X; }
		if (AlignmentX == UI::Text::Alignment::Max) { pos.X = ContainerBox.Max.X; }

		if (AlignmentY == UI::Text::Alignment::Min) { pos.Y = ContainerBox.Min.Y; }
		if (AlignmentY == UI::Text::Alignment::Mid) { pos.Y = ContainerBox.Center().Y; }
		if (AlignmentY == UI::Text::Alignment::Max) { pos.Y = ContainerBox.Max.Y; }

		TextObject.TextAlignmentX() = AlignmentX;
		TextObject.TextAlignmentY() = AlignmentY;

		TextObject.CharacterAlignmentX() = AlignmentX;
		TextObject.CharacterAlignmentY() = AlignmentY;
	}
}
void UI::Control::TextBox::PutCharactersEntrys()
{
	if (TextObject.Is())
	{
		TextObject.Text() = Text;
		TextObject.Bound() = ContainerBox;
	}
	PutAlignment();
}



std::string UI::Control::TextBox::GetText() const
{
	return Text;
}
void UI::Control::TextBox::SetText(std::string text)
{
	Text = text;
	TextCursor = Text.length();
	PutCharactersEntrys();
	PutCursor();
}



void UI::Control::TextBox::RelayUpdateBox()
{
	if (TextObject.Is())
	{
		PutCharactersEntrys();
		PutCursor();
	}
}

void UI::Control::TextBox::RelayInsertObject()
{
	if (Manager != nullptr)
	{
		if (!TextObject.Is()) { TextObject.Create(); }
	}
}
void UI::Control::TextBox::RelayRemoveObject()
{
	if (Manager == nullptr)
	{
		if (TextObject.Is()) { TextObject.Delete(); }
	}
}



void UI::Control::TextBox::RelayKey(KeyArgs args)
{
	if (!IsInteractible() || ReadOnly) { return; }

	if ((args.Action == Action::Press || args.Action == Action::Repeat))
	{
		if (args.Key == Keys::Backspace)
		{
			if (TextCursor > 0)
			{
				if (TextCursor < Text.length())
				{
					Text.erase(TextCursor - 1, 1);
					TextCursor--;
				}
				else
				{
					Text.erase(Text.length() - 1, 1);
					TextCursor = Text.length();
				}
				PutCharactersEntrys();
				PutCursor();
			}
		}
		if (args.Key == Keys::Enter)
		{
			if (TextCursor < Text.length())
			{
				Text.insert(TextCursor, 1, '\n');
				TextCursor++;
			}
			else
			{
				Text += '\n';
				TextCursor = Text.length();
			}
			PutCharactersEntrys();
			PutCursor();
		}

		if (args.Key == Keys::Home)
		{
			TextCursor = 0;
			PutCursor();
		}
		if (args.Key == Keys::End)
		{
			TextCursor = Text.length();
			PutCursor();
		}

		if (args.Key == Keys::Left)
		{
			if (TextCursor > 0)
			{
				TextCursor--;
				PutCursor();
			}
		}
		if (args.Key == Keys::Right)
		{
			if (TextCursor < Text.length())
			{
				TextCursor++;
				PutCursor();
			}
		}

		if (args.Key == Keys::Up)
		{ }
		if (args.Key == Keys::Down)
		{ }
	}
}
void UI::Control::TextBox::RelayText(TextArgs args)
{
	if (!IsInteractible() || ReadOnly) { return; }

	char c = args.Codepoint;
	if (TextCursor < Text.length())
	{
		Text.insert(TextCursor, 1, c);
		TextCursor++;
	}
	else
	{
		Text += c;
		TextCursor = Text.length();
	}
	PutCharactersEntrys();
	PutCursor();
}



// when cursor changes, move Text so Cursor is allways visible
void UI::Control::TextBox::PutCursor()
{
	if (TextObject.Is())
	{
		TextObject.ShowTextCursor();
		TextObject.TextCursorIndex() = TextCursor;
	}
}
