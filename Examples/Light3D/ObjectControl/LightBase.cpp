#include "ObjectControl/LightBase.hpp"



UI::Control::LightBase::~LightBase()
{ }
UI::Control::LightBase::LightBase()
	: GroupBox()
	, Intensity()
	, Color()
	, Object(nullptr)
{
	Intensity.Anchor.X.AnchorBoth(0, 0);
	Color.Anchor.X.AnchorBoth(0, 0);

	Intensity.Anchor.Y.AnchorMin(0);
	Color.Anchor.Y.AnchorMin(Intensity.Anchor.Y.GetMinSize());

	Anchor.X.AnchorBoth(0, 0);
	Anchor.Y.AnchorMin(0, Color.Anchor.Y.GetMinSize() + Color.AnchorMargin.Max.Y + AnchorBoarder.Max.Y + AnchorPadding.Max.Y);

	ChildInsert(Intensity);
	ChildInsert(Color);
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
