#include "ObjectData.hpp"



UI::Text::ObjectData::~ObjectData() { }

UI::Text::ObjectData::ObjectData()
	: Remove(false)
	, Display(true)
	, Text()
	, TextPosition()
	, TextAlignmentX(Alignment::Min)
	, TextAlignmentY(Alignment::Min)
	, CharacterSize(20.0f, 20.0f)
	, CharacterAlignmentX(Alignment::Max)
	, CharacterAlignmentY(Alignment::Max)
	, Bound()
	, Color()
	, DisplayTextCursor(false)
	, TextCursorIndex(0)
{ }
UI::Text::ObjectData::ObjectData(const ObjectData & other)
	: Remove(other.Remove)
	, Display(other.Display)
	, Text(other.Text)
	, TextPosition(other.TextPosition)
	, TextAlignmentX(other.TextAlignmentX)
	, TextAlignmentY(other.TextAlignmentY)
	, CharacterSize(other.CharacterSize)
	, CharacterAlignmentX(other.CharacterAlignmentX)
	, CharacterAlignmentY(other.CharacterAlignmentY)
	, Bound(other.Bound)
	, Color(other.Color)
	, DisplayTextCursor(other.DisplayTextCursor)
	, TextCursorIndex(other.TextCursorIndex)
{ }
UI::Text::ObjectData & UI::Text::ObjectData::operator=(const ObjectData & other)
{
	Remove = other.Remove;
	Display = other.Display;
	Text = other.Text;
	TextPosition = other.TextPosition;
	TextAlignmentX = other.TextAlignmentX;
	TextAlignmentY = other.TextAlignmentY;
	CharacterSize = other.CharacterSize;
	CharacterAlignmentX = other.CharacterAlignmentX;
	CharacterAlignmentY = other.CharacterAlignmentY;
	Bound = other.Bound;
	Color = other.Color;
	DisplayTextCursor = other.DisplayTextCursor;
	TextCursorIndex = other.TextCursorIndex;
	return *this;
}
