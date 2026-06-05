#include "Object.hpp"
#include "ObjectData.hpp"
#include "Manager.hpp"



bool UI::Graph::Object::Is() const { return (Data != nullptr); }

bool UI::Graph::Object::Visibility() const { return (Data -> Display); }
void UI::Graph::Object::Hide() { (Data -> Display) = false; }
void UI::Graph::Object::Full() { (Data -> Display) = true; }



BoxF2 &		UI::Graph::Object::Box() { return (Data -> Box); }



UI::Graph::Object::~Object()
{
	if (Data != nullptr)
	{
		Data -> Remove = true;
	}
}
UI::Graph::Object::Object()
	: Data(nullptr)
{ }
UI::Graph::Object::Object(const Object & other)
	: Data(Manager::Current().CopyObject(other.Data))
{ }
UI::Graph::Object & UI::Graph::Object::operator=(const Object & other)
{
	if (Data != nullptr)
	{
		Data -> Remove = true;
	}
	Data = Manager::Current().CopyObject(other.Data);
	return *this;
}



void UI::Graph::Object::Delete()
{
	if (Data != nullptr)
	{
		Data -> Remove = true;
		Data = nullptr;
	}
}
void UI::Graph::Object::Create()
{
	if (Data == nullptr)
	{
		Data = Manager::Current().PlaceObject();
	}
}
