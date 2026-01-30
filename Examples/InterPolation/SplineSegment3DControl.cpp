#include "SplineSegment3DControl.hpp"

#include "UserParameter/MouseInclude.hpp"

#include <iostream>



UI::Control::SplineSegment3D::SplineSegment3D() :
	T_Slider(),
	B_Slider(),
	C_Slider(),
	T_Text(),
	B_Text(),
	C_Text(),
	Prev_Button(),
	Next_Button(),
	Prev_Text(),
	Next_Text(),
	Object(NULL)
{
	float x = 0;
	float y = 0;

	T_Slider.Anchor.X.AnchorMin(0, 160);
	T_Slider.Anchor.Y.AnchorMin(y);
	x = T_Slider.Anchor.X.GetMinSize();

	T_Text.Anchor.X.AnchorBoth(x, 0);
	T_Text.Anchor.Y.AnchorMin(y);
	y = T_Slider.Anchor.Y.GetMinSize();

	B_Slider.Anchor.X.AnchorMin(0, 160);
	B_Slider.Anchor.Y.AnchorMin(y);
	x = B_Slider.Anchor.X.GetMinSize();

	B_Text.Anchor.X.AnchorBoth(x, 0);
	B_Text.Anchor.Y.AnchorMin(y);
	y = B_Slider.Anchor.Y.GetMinSize();

	C_Slider.Anchor.X.AnchorMin(0, 160);
	C_Slider.Anchor.Y.AnchorMin(y);
	x = C_Slider.Anchor.X.GetMinSize();

	C_Text.Anchor.X.AnchorBoth(x, 0);
	C_Text.Anchor.Y.AnchorMin(y);
	y = C_Slider.Anchor.Y.GetMinSize();

	Prev_Button.Anchor.X.AnchorMin(0);
	Prev_Button.Anchor.Y.AnchorMin(y);
	x = Prev_Button.Anchor.X.GetMinSize();

	Prev_Text.Anchor.X.AnchorBoth(x, 0);
	Prev_Text.Anchor.Y.AnchorMin(y);
	y = Prev_Text.Anchor.Y.GetMinSize();

	Next_Button.Anchor.X.AnchorMin(0);
	Next_Button.Anchor.Y.AnchorMin(y);
	x = Next_Button.Anchor.X.GetMinSize();

	Next_Text.Anchor.X.AnchorBoth(x, 0);
	Next_Text.Anchor.Y.AnchorMin(y);
	y = Next_Text.Anchor.Y.GetMinSize();

	T_Slider.SliderMin = -1.0f;
	B_Slider.SliderMin = -1.0f;
	C_Slider.SliderMin = -1.0f;

	T_Slider.SliderMax = +2.0f;
	B_Slider.SliderMax = +2.0f;
	C_Slider.SliderMax = +2.0f;

	T_Text.ReadOnly = true;
	B_Text.ReadOnly = true;
	C_Text.ReadOnly = true;

	Next_Text.ReadOnly = true;
	Prev_Text.ReadOnly = true;

	T_Slider.ValueChangedFunc.Change(this, &UI::Control::SplineSegment3D::SplineSegment3D::T_Slider_CallBack_Func);
	B_Slider.ValueChangedFunc.Change(this, &UI::Control::SplineSegment3D::SplineSegment3D::B_Slider_CallBack_Func);
	C_Slider.ValueChangedFunc.Change(this, &UI::Control::SplineSegment3D::SplineSegment3D::C_Slider_CallBack_Func);
	Next_Button.ClickFunc.Change(this, &UI::Control::SplineSegment3D::SplineSegment3D::Next_Button_CallBack_Func);
	Prev_Button.ClickFunc.Change(this, &UI::Control::SplineSegment3D::SplineSegment3D::Prev_Button_CallBack_Func);

	ChildInsert(&T_Slider);
	ChildInsert(&T_Text);
	ChildInsert(&B_Slider);
	ChildInsert(&B_Text);
	ChildInsert(&C_Slider);
	ChildInsert(&C_Text);

	ChildInsert(&Next_Button);
	ChildInsert(&Next_Text);
	ChildInsert(&Prev_Button);
	ChildInsert(&Prev_Text);

	Anchor.X.Anchor = AnchorType::Min;
	Anchor.Y.Anchor = AnchorType::Min;
	Anchor.X.SetMinDist(0);
	Anchor.Y.SetMinDist(0);
	Anchor.X.SetSize(320);
	Anchor.Y.SetSize((25 + 5 * 2) * 5);
}
UI::Control::SplineSegment3D::~SplineSegment3D()
{ }



void UI::Control::SplineSegment3D::ChangeObject(::SplineSegment3D * obj)
{
	Object = obj;
	T_Slider.SetValue(Object -> T);
	B_Slider.SetValue(Object -> B);
	C_Slider.SetValue(Object -> C);
	if (Object -> Prev == NULL) { Prev_Text.SetText("Prev:false"); } else { Prev_Text.SetText("Prev:true"); }
	if (Object -> Next == NULL) { Next_Text.SetText("Next:false"); } else { Next_Text.SetText("Next:true"); }
}



void UI::Control::SplineSegment3D::T_Slider_CallBack_Func(float val)
{
	T_Text.SetText(std::to_string((float)val));
	if (Object != NULL) { Object -> T = val; }
}
void UI::Control::SplineSegment3D::B_Slider_CallBack_Func(float val)
{
	B_Text.SetText(std::to_string((float)val));
	if (Object != NULL) { Object -> B = val; }
}
void UI::Control::SplineSegment3D::C_Slider_CallBack_Func(float val)
{
	C_Text.SetText(std::to_string((float)val));
	if (Object != NULL) { Object -> C = val; }
}
void UI::Control::SplineSegment3D::Prev_Button_CallBack_Func(UserParameter::Mouse::Click params)
{
	if (params.Action.IsPress())
	{
		if (Object -> Prev != NULL)
		{
			ChangeObject(Object -> Prev);
		}
	}
}
void UI::Control::SplineSegment3D::Next_Button_CallBack_Func(UserParameter::Mouse::Click params)
{
	if (params.Action.IsPress())
	{
		if (Object -> Next != NULL)
		{
			ChangeObject(Object -> Next);
		}
	}
}
