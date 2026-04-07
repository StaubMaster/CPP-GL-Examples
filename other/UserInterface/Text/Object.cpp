#include "Object.hpp"
#include "ObjectData.hpp"
#include "Manager.hpp"



bool			UI::Text::Object::Is() const { return (Data != nullptr); }
std::string &	UI::Text::Object::String() const { return (Data -> Text); }

Point2D &		UI::Text::Object::Pos() const { return (Data -> Pos); }
AxisBox2D &		UI::Text::Object::Bound() const { return (Data -> Bound); }

bool UI::Text::Object::Visibility() const { return (Data -> Display); }
void UI::Text::Object::Hide() const { (Data -> Display) = false; }
void UI::Text::Object::Full() const { (Data -> Display) = true; }



UI::Text::Object::~Object()
{
	if (Data != nullptr)
	{
		Data -> Remove = true;
	}
}
UI::Text::Object::Object()
	: Data(nullptr)
{ }
UI::Text::Object::Object(const Object & other)
	: Data(Manager::Current().CopyObject(other.Data))
{ }
UI::Text::Object & UI::Text::Object::operator=(const Object & other)
{
	if (Data != nullptr)
	{
		Data -> Remove = true;
	}
	Data = Manager::Current().CopyObject(other.Data);
	return *this;
}



void UI::Text::Object::Delete()
{
	if (Data != nullptr)
	{
		Data -> Remove = true;
		Data = nullptr;
	}
}
void UI::Text::Object::Create()
{
	if (Data == nullptr)
	{
		Data = Manager::Current().PlaceObject();
	}
}
