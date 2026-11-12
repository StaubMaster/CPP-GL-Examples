#include "Control/Controls/TextBox.hpp"
#include "Control/General/Manager.hpp"
#include "AnchorEnum.hpp"

#include "Text/Manager.hpp"
#include <math.h>



UI::Control::TextBox::TextBox()
{
	Anchor.X.Anchor = AnchorType::Min;
	Anchor.Y.Anchor = AnchorType::Min;
	AnchorSize = VectorF2(50, 25);

	float padding = 0;
	AnchorPadding = BoxF2(VectorF2(padding, padding), VectorF2(padding, padding));

	ColorDefault = ColorF4(1.0f, 1.0f, 1.0f);
	ColorHover = ColorF4(0.875f, 0.875f, 0.875f);

	AlignmentX = UI::Text::Alignment::Min;
	AlignmentY = UI::Text::Alignment::Min;
}



#include "User/MouseArgs.hpp"
#include "User/KeyBoardArgs.hpp"
#include "HoverArgs.hpp"
void UI::Control::TextBox::RelayKey(KeyArgs args)
{
	if (!IsInteractible() || ReadOnly) { return; }

	if ((args.Action == Action::Press || args.Action == Action::Repeat))
	{
		if (args.Key == Keys::Backspace)
		{
			if (TextObjectData.TextCursorIndex > 0)
			{
				if (TextObjectData.TextCursorIndex < TextObjectData.Text.length())
				{
					TextObjectData.Text.erase(TextObjectData.TextCursorIndex - 1, 1);
					TextObjectData.TextCursorIndex--;
				}
				else
				{
					TextObjectData.Text.erase(TextObjectData.Text.length() - 1, 1);
					TextObjectData.TextCursorIndex = TextObjectData.Text.length();
				}
			}
		}
		if (args.Key == Keys::Enter)
		{
			if (TextObjectData.TextCursorIndex < TextObjectData.Text.length())
			{
				TextObjectData.Text.insert(TextObjectData.TextCursorIndex, 1, '\n');
				TextObjectData.TextCursorIndex++;
			}
			else
			{
				TextObjectData.Text += '\n';
				TextObjectData.TextCursorIndex = TextObjectData.Text.length();
			}
		}

		if (args.Key == Keys::Home)
		{
			TextObjectData.TextCursorIndex = 0;
		}
		if (args.Key == Keys::End)
		{
			TextObjectData.TextCursorIndex = TextObjectData.Text.length();
		}

		if (args.Key == Keys::Left)
		{
			if (TextObjectData.TextCursorIndex > 0)
			{
				TextObjectData.TextCursorIndex--;
			}
		}
		if (args.Key == Keys::Right)
		{
			if (TextObjectData.TextCursorIndex < TextObjectData.Text.length())
			{
				TextObjectData.TextCursorIndex++;
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
	if (TextObjectData.TextCursorIndex < TextObjectData.Text.length())
	{
		TextObjectData.Text.insert(TextObjectData.TextCursorIndex, 1, c);
		TextObjectData.TextCursorIndex++;
	}
	else
	{
		TextObjectData.Text += c;
		TextObjectData.TextCursorIndex = TextObjectData.Text.length();
	}
}
