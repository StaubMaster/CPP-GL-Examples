#include "ValueTypeUI/VectorF3.hpp"



UI::Control::VectorF3::~VectorF3()
{ }
UI::Control::VectorF3::VectorF3(const char * name)
	: PropertyControl(name)
	, X()
	, Y()
	, Z()
	, Object(nullptr)
{
	X.Anchor.X.AnchorBoth(0, 0);
	Y.Anchor.X.AnchorBoth(0, 0);
	Z.Anchor.X.AnchorBoth(0, 0);

	ChildInsert(X);
	ChildInsert(Y);
	ChildInsert(Z);

	HideProperty();
}



#include "UnitToString.hpp"
#include <sstream>

void UI::Control::VectorF3::Update()
{
	if (Object != nullptr)
	{
		std::stringstream ss;
		ss.str(std::string()); ss << "X:" << ToString(Object -> X, 3); X.SetText(ss.str());
		ss.str(std::string()); ss << "Y:" << ToString(Object -> Y, 3); Y.SetText(ss.str());
		ss.str(std::string()); ss << "Z:" << ToString(Object -> Z, 3); Z.SetText(ss.str());
	}
	else
	{
		X.SetText("X:");
		Y.SetText("Y:");
		Z.SetText("Z:");
	}
}

void UI::Control::VectorF3::Change(::VectorF3 * obj)
{
	Object = obj;
}
