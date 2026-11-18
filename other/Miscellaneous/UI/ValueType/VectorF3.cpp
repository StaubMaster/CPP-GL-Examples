#include "UI/ValueType/VectorF3.hpp"



UI::VectorF3::VectorF3(const char * name)
	: NestedProperty(name)
	, X()
	, Y()
	, Z()
	, Object(nullptr)
{
	X.Make_Anchor_X_Both(nullptr, nullptr);
	Y.Make_Anchor_X_Both(nullptr, nullptr);
	Z.Make_Anchor_X_Both(nullptr, nullptr);

	ChildInsert(X);
	ChildInsert(Y);
	ChildInsert(Z);

	Minimize();
}



#include "UnitToString.hpp"
#include <sstream>

void UI::VectorF3::Syncronize()
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

void UI::VectorF3::Change(::VectorF3 * obj)
{
	Object = obj;
}
