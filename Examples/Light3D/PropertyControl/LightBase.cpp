#include "PropertyControl/LightBase.hpp"



UI::Control::LightBase::~LightBase()
{ }
UI::Control::LightBase::LightBase()
	: GroupBox()
	, Intensity()
	, Color("Color")
	, Object(nullptr)
{
	Intensity.Anchor.X.AnchorBoth(0, 0);
	Color.Anchor.X.AnchorBoth(0, 0);

	ChildInsert(Intensity);
	ChildInsert(Color);

	AnchorFitChildrenY();
}



#include "General/UnitToString.hpp"
#include <sstream>

void UI::Control::LightBase::Change(::LightBase * obj)
{
	Object = obj;
	if (Object != nullptr)
	{
		std::stringstream ss;
		ss.str(std::string()); ss << "Intensity:" << ToString(Object -> Intensity); Intensity.SetText(ss.str());
		Color.Change(&(Object -> Color));
	}
	else
	{
		Intensity.SetText("Intensity:");
		Color.Change(nullptr);
	}
}
