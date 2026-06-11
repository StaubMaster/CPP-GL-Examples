#include "PropertyControl/VectorF3.hpp"



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

	AnchorFitChildrenY();
}



#include "General/UnitToString.hpp"
#include <sstream>

void UI::Control::VectorF3::Change(::VectorF3 * obj)
{
	Object = obj;
	if (Object != nullptr)
	{
		std::stringstream ss;
		ss.str(std::string()); ss << "X:" << ToString(Object -> X); X.SetText(ss.str());
		ss.str(std::string()); ss << "Y:" << ToString(Object -> Y); Y.SetText(ss.str());
		ss.str(std::string()); ss << "Z:" << ToString(Object -> Z); Z.SetText(ss.str());
	}
	else
	{
		X.SetText("X:");
		Y.SetText("Y:");
		Z.SetText("Z:");
	}
}
