#include "UI/ValueType/EulerAngle3D.hpp"



UI::EulerAngle3D::EulerAngle3D(const char * name)
	: NestedProperty(name)
	, Z0()
	, X1()
	, Y2()
	, Object(nullptr)
{
	Z0.Make_Anchor_X_Both(nullptr, nullptr);
	X1.Make_Anchor_X_Both(nullptr, nullptr);
	Y2.Make_Anchor_X_Both(nullptr, nullptr);

	ChildInsert(Z0);
	ChildInsert(X1);
	ChildInsert(Y2);

	Minimize();
}



#include "UnitToString.hpp"
#include <sstream>

void UI::EulerAngle3D::Syncronize()
{
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

void UI::EulerAngle3D::Change(::EulerAngle3D * obj)
{
	Object = obj;
}
