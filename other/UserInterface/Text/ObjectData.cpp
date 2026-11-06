#include "ObjectData.hpp"



UI::Text::ObjectData::ObjectData()
//	: CharacterSize(20.0f, 20.0f)
	: CharacterSize(12.0f, 12.0f)
{ }



void UI::Text::ObjectData::AlignTopLeft()
{
	TextAlignmentX = UI::Text::Alignment::Min;
	TextAlignmentY = UI::Text::Alignment::Min;
	CharacterAlignmentX = UI::Text::Alignment::Min;
	CharacterAlignmentY = UI::Text::Alignment::Min;
}
void UI::Text::ObjectData::AlignTopMiddle()
{
	TextAlignmentX = UI::Text::Alignment::Mid;
	TextAlignmentY = UI::Text::Alignment::Min;
	CharacterAlignmentX = UI::Text::Alignment::Mid;
	CharacterAlignmentY = UI::Text::Alignment::Min;
}
void UI::Text::ObjectData::AlignTopRight()
{
	TextAlignmentX = UI::Text::Alignment::Max;
	TextAlignmentY = UI::Text::Alignment::Min;
	CharacterAlignmentX = UI::Text::Alignment::Max;
	CharacterAlignmentY = UI::Text::Alignment::Min;
}
void UI::Text::ObjectData::AlignMiddleLeft()
{
	TextAlignmentX = UI::Text::Alignment::Min;
	TextAlignmentY = UI::Text::Alignment::Mid;
	CharacterAlignmentX = UI::Text::Alignment::Min;
	CharacterAlignmentY = UI::Text::Alignment::Mid;
}
void UI::Text::ObjectData::AlignMiddleMiddle()
{
	TextAlignmentX = UI::Text::Alignment::Mid;
	TextAlignmentY = UI::Text::Alignment::Mid;
	CharacterAlignmentX = UI::Text::Alignment::Mid;
	CharacterAlignmentY = UI::Text::Alignment::Mid;
}
void UI::Text::ObjectData::AlignMiddleRight()
{
	TextAlignmentX = UI::Text::Alignment::Max;
	TextAlignmentY = UI::Text::Alignment::Mid;
	CharacterAlignmentX = UI::Text::Alignment::Max;
	CharacterAlignmentY = UI::Text::Alignment::Mid;
}
void UI::Text::ObjectData::AlignBottomLeft()
{
	TextAlignmentX = UI::Text::Alignment::Min;
	TextAlignmentY = UI::Text::Alignment::Max;
	CharacterAlignmentX = UI::Text::Alignment::Min;
	CharacterAlignmentY = UI::Text::Alignment::Max;
}
void UI::Text::ObjectData::AlignBottomMiddle()
{
	TextAlignmentX = UI::Text::Alignment::Mid;
	TextAlignmentY = UI::Text::Alignment::Max;
	CharacterAlignmentX = UI::Text::Alignment::Mid;
	CharacterAlignmentY = UI::Text::Alignment::Max;
}
void UI::Text::ObjectData::AlignBottomRight()
{
	TextAlignmentX = UI::Text::Alignment::Max;
	TextAlignmentY = UI::Text::Alignment::Max;
	CharacterAlignmentX = UI::Text::Alignment::Max;
	CharacterAlignmentY = UI::Text::Alignment::Max;
}
