#include "ObjectData.hpp"



UI::Control::ObjectData::~ObjectData()
{ }
UI::Control::ObjectData::ObjectData()
	: Remove(false)
	, Display(true)
	, Box()
	, Layer()
	, Color()
{ }
UI::Control::ObjectData::ObjectData(const ObjectData & other)
	: Remove(other.Remove)
	, Display(other.Display)
	, Box(other.Box)
	, Layer(other.Layer)
	, Color(other.Color)
{ }
UI::Control::ObjectData & UI::Control::ObjectData::operator=(const ObjectData & other)
{
	Remove = other.Remove;
	Display = other.Display;
	Box = other.Box;
	Layer = other.Layer;
	Color = other.Color;
	return *this;
}
