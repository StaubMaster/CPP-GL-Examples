#include "ObjectData.hpp"



UI::Text::ObjectData::~ObjectData()
{ }

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
