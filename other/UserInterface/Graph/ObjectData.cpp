#include "ObjectData.hpp"



UI::Graph::ObjectData::~ObjectData()
{ }
UI::Graph::ObjectData::ObjectData()
	: Remove(false)
	, Display(true)
	, Box()
	, Values(nullptr)
	, Col()
{ }
UI::Graph::ObjectData::ObjectData(const ObjectData & other)
	: Remove(other.Remove)
	, Display(other.Display)
	, Box(other.Box)
	, Values(other.Values)
	, Col(other.Col)
{ }
UI::Graph::ObjectData & UI::Graph::ObjectData::operator=(const ObjectData & other)
{
	Remove = other.Remove;
	Display = other.Display;
	Box = other.Box;
	Values = other.Values;
	Col = other.Col;
	return *this;
}
