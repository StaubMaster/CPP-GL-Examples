#include "ObjectControl/EulerAngle3D.hpp"



UI::Control::EulerAngle3D::~EulerAngle3D()
{ }
UI::Control::EulerAngle3D::EulerAngle3D()
	: GroupBox()
	, Z0()
	, X1()
	, Y2()
	, Object(nullptr)
{
	Z0.Anchor.X.AnchorBoth(0, 0);
	X1.Anchor.X.AnchorBoth(0, 0);
	Y2.Anchor.X.AnchorBoth(0, 0);

	Z0.Anchor.Y.AnchorMin(0);
	X1.Anchor.Y.AnchorMin(Z0.Anchor.Y.GetMinSize());
	Y2.Anchor.Y.AnchorMin(X1.Anchor.Y.GetMinSize());

	Anchor.X.AnchorBoth(0, 0);
	Anchor.Y.AnchorMin(0, Y2.Anchor.Y.GetMinSize() + Y2.AnchorMargin.Max.Y + AnchorBoarder.Max.Y + AnchorPadding.Max.Y);

	ChildInsert(Z0);
	ChildInsert(X1);
	ChildInsert(Y2);
}



#include "General/UnitToString.hpp"
#include <sstream>

void UI::Control::EulerAngle3D::Change(::EulerAngle3D * obj)
{
	Object = obj;
	if (Object != nullptr)
	{
		std::stringstream ss;
		ss.str(std::string()); ss << "Z0:" << ToString(Object -> Z0.ToDegrees()); Z0.SetText(ss.str());
		ss.str(std::string()); ss << "X1:" << ToString(Object -> X1.ToDegrees()); X1.SetText(ss.str());
		ss.str(std::string()); ss << "Y2:" << ToString(Object -> Y2.ToDegrees()); Y2.SetText(ss.str());
	}
	else
	{
		Z0.SetText("Z0:");
		X1.SetText("X1:");
		Y2.SetText("Y2:");
	}
}
