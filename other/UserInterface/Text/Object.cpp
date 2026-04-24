#include "Object.hpp"
#include "ObjectData.hpp"
#include "Manager.hpp"



bool			UI::Text::Object::Is() const { return (Data != nullptr); }
std::string &	UI::Text::Object::String() { return (Data -> Text); }

Point2D &				UI::Text::Object::TextPosition() { return (Data -> TextPosition); }
UI::Text::Alignment &	UI::Text::Object::TextAlignmentX() { return (Data -> TextAlignmentX); }
UI::Text::Alignment &	UI::Text::Object::TextAlignmentY() { return (Data -> TextAlignmentY); }

Point2D &				UI::Text::Object::CharacterSize() { return (Data -> CharacterSize); }
UI::Text::Alignment &	UI::Text::Object::CharacterAlignmentX() { return (Data -> CharacterAlignmentX); }
UI::Text::Alignment &	UI::Text::Object::CharacterAlignmentY() { return (Data -> CharacterAlignmentY); }

AxisBox2D &		UI::Text::Object::Bound() { return (Data -> Bound); }
ColorF4 &		UI::Text::Object::Color() { return (Data -> Color); }

bool UI::Text::Object::Visibility() const { return (Data -> Display); }
void UI::Text::Object::Hide() { (Data -> Display) = false; }
void UI::Text::Object::Full() { (Data -> Display) = true; }



void UI::Text::Object::AlignTopLeft()
{
	Data -> TextAlignmentX = UI::Text::Alignment::Min;
	Data -> TextAlignmentY = UI::Text::Alignment::Min;
	Data -> CharacterAlignmentX = UI::Text::Alignment::Max;
	Data -> CharacterAlignmentY = UI::Text::Alignment::Max;
}
void UI::Text::Object::AlignTopMiddle()
{
	Data -> TextAlignmentX = UI::Text::Alignment::Mid;
	Data -> TextAlignmentY = UI::Text::Alignment::Min;
	Data -> CharacterAlignmentX = UI::Text::Alignment::Mid;
	Data -> CharacterAlignmentY = UI::Text::Alignment::Max;
}
void UI::Text::Object::AlignTopRight()
{
	Data -> TextAlignmentX = UI::Text::Alignment::Max;
	Data -> TextAlignmentY = UI::Text::Alignment::Min;
	Data -> CharacterAlignmentX = UI::Text::Alignment::Min;
	Data -> CharacterAlignmentY = UI::Text::Alignment::Max;
}
void UI::Text::Object::AlignMiddleLeft()
{
	Data -> TextAlignmentX = UI::Text::Alignment::Min;
	Data -> TextAlignmentY = UI::Text::Alignment::Mid;
	Data -> CharacterAlignmentX = UI::Text::Alignment::Max;
	Data -> CharacterAlignmentY = UI::Text::Alignment::Mid;
}
void UI::Text::Object::AlignMiddleMiddle()
{
	Data -> TextAlignmentX = UI::Text::Alignment::Mid;
	Data -> TextAlignmentY = UI::Text::Alignment::Mid;
	Data -> CharacterAlignmentX = UI::Text::Alignment::Mid;
	Data -> CharacterAlignmentY = UI::Text::Alignment::Mid;
}
void UI::Text::Object::AlignMiddleRight()
{
	Data -> TextAlignmentX = UI::Text::Alignment::Max;
	Data -> TextAlignmentY = UI::Text::Alignment::Mid;
	Data -> CharacterAlignmentX = UI::Text::Alignment::Min;
	Data -> CharacterAlignmentY = UI::Text::Alignment::Mid;
}
void UI::Text::Object::AlignBottomLeft()
{
	Data -> TextAlignmentX = UI::Text::Alignment::Min;
	Data -> TextAlignmentY = UI::Text::Alignment::Max;
	Data -> CharacterAlignmentX = UI::Text::Alignment::Max;
	Data -> CharacterAlignmentY = UI::Text::Alignment::Min;
}
void UI::Text::Object::AlignBottomMiddle()
{
	Data -> TextAlignmentX = UI::Text::Alignment::Mid;
	Data -> TextAlignmentY = UI::Text::Alignment::Max;
	Data -> CharacterAlignmentX = UI::Text::Alignment::Mid;
	Data -> CharacterAlignmentY = UI::Text::Alignment::Min;
}
void UI::Text::Object::AlignBottomRight()
{
	Data -> TextAlignmentX = UI::Text::Alignment::Max;
	Data -> TextAlignmentY = UI::Text::Alignment::Max;
	Data -> CharacterAlignmentX = UI::Text::Alignment::Min;
	Data -> CharacterAlignmentY = UI::Text::Alignment::Min;
}



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
