#include "ValueTypeUI/ColorF4.hpp"



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

	R.ValueMin.X = 0.0f;
	R.ValueMax.X = 1.0f;
	R.ValueXChangedFunc.Assign(this, &ColorF4::RFunc);

	G.ValueMin.X = 0.0f;
	G.ValueMax.X = 1.0f;
	G.ValueXChangedFunc.Assign(this, &ColorF4::GFunc);

	B.ValueMin.X = 0.0f;
	B.ValueMax.X = 1.0f;
	B.ValueXChangedFunc.Assign(this, &ColorF4::BFunc);

	ChildInsert(R);
	ChildInsert(G);
	ChildInsert(B);

	HideProperty();
}



#include "UnitToString.hpp"
#include <sstream>

void UI::Control::ColorF4::Update()
{
	if (Object != nullptr)
	{
		R.SetValueX(Object -> R);
		G.SetValueX(Object -> G);
		B.SetValueX(Object -> B);
	}
	else
	{
		R.SetText("R:");
		G.SetText("G:");
		B.SetText("B:");
	}
}
void UI::Control::ColorF4::Change(::ColorF4 * obj)
{
	Object = obj;
}



void UI::Control::ColorF4::RFunc(float val)
{
	if (Object == nullptr) { return; }
	Object -> R = val;
	std::stringstream ss;
	ss << "R:" << ToString(Object -> R, 2);
	R.SetText(ss.str());
}
void UI::Control::ColorF4::GFunc(float val)
{
	if (Object == nullptr) { return; }
	Object -> G = val;
	std::stringstream ss;
	ss << "G:" << ToString(Object -> G, 2);
	G.SetText(ss.str());
}
void UI::Control::ColorF4::BFunc(float val)
{
	if (Object == nullptr) { return; }
	Object -> B = val;
	std::stringstream ss;
	ss << "B:" << ToString(Object -> B, 2);
	B.SetText(ss.str());
}
