#include "ObjectData.hpp"



UI::Text::ObjectData::~ObjectData() { }

UI::Text::ObjectData::ObjectData()
	: Text()
	, AlignmentX(Alignment::Min)
	, AlignmentY(Alignment::Min)
	, Pos()
	, Bound()
	, Remove(false)
	, Display(true)
{ }
UI::Text::ObjectData::ObjectData(const ObjectData & other)
	: Text(other.Text)
	, AlignmentX(other.AlignmentX)
	, AlignmentY(other.AlignmentY)
	, Pos(other.Pos)
	, Bound(other.Bound)
	, Remove(other.Remove)
	, Display(other.Display)
{ }
UI::Text::ObjectData & UI::Text::ObjectData::operator=(const ObjectData & other)
{
	Text = other.Text;
	AlignmentX = other.AlignmentX;
	AlignmentY = other.AlignmentY;
	Pos = other.Pos;
	Bound = other.Bound;
	Remove = other.Remove;
	Display = other.Display;
	return *this;
}
