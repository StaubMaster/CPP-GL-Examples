#include "ObjectControl/VectorF3.hpp"



UI::Control::VectorF3::~VectorF3()
{ }
UI::Control::VectorF3::VectorF3()
	: GroupBox()
	, X()
	, Y()
	, Z()
	, Object(nullptr)
{
	X.Anchor.X.AnchorBoth(0, 0);
	Y.Anchor.X.AnchorBoth(0, 0);
	Z.Anchor.X.AnchorBoth(0, 0);

	X.Anchor.Y.AnchorMin(0);
	Y.Anchor.Y.AnchorMin(X.Anchor.Y.GetMinSize());
	Z.Anchor.Y.AnchorMin(Y.Anchor.Y.GetMinSize());

	Anchor.X.AnchorBoth(0, 0);
	Anchor.Y.AnchorMin(0, Z.Anchor.Y.GetMinSize() + Z.AnchorMargin.Max.Y + AnchorBoarder.Max.Y + AnchorPadding.Max.Y);

	ChildInsert(X);
	ChildInsert(Y);
	ChildInsert(Z);
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
