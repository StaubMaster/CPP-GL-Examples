#include "Object.hpp"
#include "ObjectData.hpp"
#include "Manager.hpp"



bool UI::Control::Object::Is() const { return (Data != nullptr); }

bool UI::Control::Object::Visibility() const { return (Data -> Display); }
void UI::Control::Object::Hide() { (Data -> Display) = false; }
void UI::Control::Object::Full() { (Data -> Display) = true; }



float &		UI::Control::Object::Depth() { return (Data -> Depth); }
BoxF2 &		UI::Control::Object::Box() { return (Data -> Box); }
ColorF4 &	UI::Control::Object::Color() { return (Data -> Color); }
BoxF2 &		UI::Control::Object::Bound() { return (Data -> Bound); }



UI::Control::Object::~Object()
{
	if (Data != nullptr)
	{
		Data -> Remove = true;
	}
}
UI::Control::Object::Object()
	: Data(nullptr)
{ }
UI::Control::Object::Object(const Object & other)
	: Data(Manager::Current().CopyObject(other.Data))
{ }
UI::Control::Object & UI::Control::Object::operator=(const Object & other)
{
	if (Data != nullptr)
	{
		Data -> Remove = true;
	}
	Data = Manager::Current().CopyObject(other.Data);
	return *this;
}



void UI::Control::Object::Delete()
{
	if (Data != nullptr)
	{
		Data -> Remove = true;
		Data = nullptr;
	}
}
void UI::Control::Object::Create()
{
	if (Data == nullptr)
	{
		Data = Manager::Current().PlaceObject();
	}
}
