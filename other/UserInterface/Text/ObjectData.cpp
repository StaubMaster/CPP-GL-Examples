#include "ObjectData.hpp"



UI::Text::ObjectData::~ObjectData() { }

UI::Text::ObjectData::ObjectData()
	: Text()
	, TextPosition()
	, TextAlignmentX(Alignment::Min)
	, TextAlignmentY(Alignment::Min)
	, CharacterSize(20.0f, 20.0f)
	, CharacterAlignmentX(Alignment::Max)
	, CharacterAlignmentY(Alignment::Max)
	, Bound()
	, Color()
	, Remove(false)
	, Display(true)
{ }
UI::Text::ObjectData::ObjectData(const ObjectData & other)
	: Text(other.Text)
	, TextPosition(other.TextPosition)
	, TextAlignmentX(other.TextAlignmentX)
	, TextAlignmentY(other.TextAlignmentY)
	, CharacterSize(other.CharacterSize)
	, CharacterAlignmentX(other.CharacterAlignmentX)
	, CharacterAlignmentY(other.CharacterAlignmentY)
	, Bound(other.Bound)
	, Color(other.Color)
	, Remove(other.Remove)
	, Display(other.Display)
{ }
UI::Text::ObjectData & UI::Text::ObjectData::operator=(const ObjectData & other)
{
	Text = other.Text;
	TextPosition = other.TextPosition;
	TextAlignmentX = other.TextAlignmentX;
	TextAlignmentY = other.TextAlignmentY;
	CharacterSize = other.CharacterSize;
	CharacterAlignmentX = other.CharacterAlignmentX;
	CharacterAlignmentY = other.CharacterAlignmentY;
	Bound = other.Bound;
	Color = other.Color;
	Remove = other.Remove;
	Display = other.Display;
	return *this;
}
