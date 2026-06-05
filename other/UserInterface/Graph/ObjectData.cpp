#include "ObjectData.hpp"



UI::Graph::ObjectData::~ObjectData()
{ }
UI::Graph::ObjectData::ObjectData()
	: Remove(false)
	, Display(true)
	, Box()
	, Center()
	, Magnitede()
	, Col()
	, Values(nullptr)
{ }
UI::Graph::ObjectData::ObjectData(const ObjectData & other)
	: Remove(other.Remove)
	, Display(other.Display)
	, Box(other.Box)
	, Center(other.Center)
	, Magnitede(other.Magnitede)
	, Col(other.Col)
	, Values(other.Values)
{ }
UI::Graph::ObjectData & UI::Graph::ObjectData::operator=(const ObjectData & other)
{
	Remove = other.Remove;
	Display = other.Display;
	Box = other.Box;
	Center = other.Center;
	Magnitede = other.Magnitede;
	Col = other.Col;
	Values = other.Values;
	return *this;
}
