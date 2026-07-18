#include "Control/Graph.hpp"



UI::Control::Graph::~Graph()
{ }
UI::Control::Graph::Graph()
	: UI::Control::Base()
	, Center(64)
	, Magnitude(8)
	, Values(64)
	, GraphObject()
{
	ColorDefault = ColorF4(0.625f, 0.625f, 0.625f);
	ColorHover = ColorF4(0.5f, 0.5f, 0.5f);
}



#include "../Graph/ObjectData.hpp"

void UI::Control::Graph::RelayUpdateBox()
{
	if (GraphObject.Is())
	{
		GraphObject.Box() = ContainerBox;
		GraphObject.Data -> Center = Center;
		GraphObject.Data -> Magnitede = Magnitude;
		GraphObject.Data -> Col = ColorF4(0, 1, 0);
		GraphObject.Data -> Values = &Values;
	}
}
void UI::Control::Graph::RelayInsertObject()
{
	if (!GraphObject.Is() && Manager != nullptr)
	{
		GraphObject.Create();
	}
}
void UI::Control::Graph::RelayRemoveObject()
{
	if (GraphObject.Is() || Manager == nullptr)
	{
		GraphObject.Delete();
	}
}
