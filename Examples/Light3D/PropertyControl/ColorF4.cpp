#include "PropertyControl/ColorF4.hpp"



UI::Control::ColorF4::~ColorF4()
{ }
UI::Control::ColorF4::ColorF4(const char * name)
	: PropertyControl(name)
	, R()
	, G()
	, B()
	, Object(nullptr)
{
	R.Anchor.X.AnchorBoth(0, 0);
	G.Anchor.X.AnchorBoth(0, 0);
	B.Anchor.X.AnchorBoth(0, 0);

	ChildInsert(R);
	ChildInsert(G);
	ChildInsert(B);

	AnchorFitChildrenY();
}



#include "General/UnitToString.hpp"
#include <sstream>

void UI::Control::ColorF4::Change(::ColorF4 * obj)
{
	Object = obj;
	if (Object != nullptr)
	{
		std::stringstream ss;
		ss.str(std::string()); ss << "R:" << ToString(Object -> R); R.SetText(ss.str());
		ss.str(std::string()); ss << "G:" << ToString(Object -> G); G.SetText(ss.str());
		ss.str(std::string()); ss << "B:" << ToString(Object -> B); B.SetText(ss.str());
	}
	else
	{
		R.SetText("R:");
		G.SetText("G:");
		B.SetText("B:");
	}
}
