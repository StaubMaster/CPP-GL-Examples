#include "Control/Controls/Graph.hpp"



UI::Control_::Graph::Graph()
	: UI::Control_::Base()
	, Center(64)
	, Magnitude(8)
	, Values(64)
	, GraphObject()
{
	ColorDefault = ColorF4(0.625f, 0.625f, 0.625f);
	//ColorHover = ColorF4(0.5f, 0.5f, 0.5f);
}



#include "Graph/ObjectData.hpp"

void UI::Control_::Graph::Update()
{
	Base::Update();
	if (GraphObject.Is())
	{
		GraphObject.Box() = BoxContent();
		GraphObject.Data -> Center = Center;
		GraphObject.Data -> Magnitede = Magnitude;
		GraphObject.Data -> Col = ColorF4(0, 1, 0);
		GraphObject.Data -> Values = &Values;
	}
}
void UI::Control_::Graph::RelayShow()
{
	Base::RelayShow();
	if (!GraphObject.Is() && _Manager() != nullptr)
	{
		GraphObject.Create();
	}
}
void UI::Control_::Graph::RelayHide()
{
	Base::RelayHide();
	if (GraphObject.Is() || _Manager() == nullptr)
	{
		GraphObject.Delete();
	}
}
