#ifndef  SPLINE_SEGMENT_3D_CONTROL_HPP
# define SPLINE_SEGMENT_3D_CONTROL_HPP

# include "Spline/SplineSegment3D.hpp"
# include "UI/ControlsInclude.hpp"
# include "UI/CallBack/Object.hpp"

# include <iostream>

/*
GroupBox
{
	this:	Pointer Address
	Prev:	Pointer Address
	Next:	Pointer Address
	T:	0.0
	B:	0.0
	C:	0.0
}
*/

namespace UI
{
namespace Control
{
class SplineSegment3D : public GroupBox
{
	public:
	Slider	T_Slider;
	Slider	B_Slider;
	Slider	C_Slider;

	TextBox	T_Text;
	TextBox	B_Text;
	TextBox	C_Text;

	private:
	//ObjectCallBack<SplineSegment3D>	T_Slider_CallBack;
	//ObjectCallBack<SplineSegment3D>	B_Slider_CallBack;
	//ObjectCallBack<SplineSegment3D>	C_Slider_CallBack;

	::SplineSegment3D * Object;

	public:
	SplineSegment3D(UI::Text::Manager & text_manager) :
		T_Slider(),
		B_Slider(),
		C_Slider(),
		T_Text(text_manager),
		B_Text(text_manager),
		C_Text(text_manager),
		//T_Slider_CallBack(this, &T_Slider_CallBack_Func),
		//B_Slider_CallBack(this, &B_Slider_CallBack_Func),
		//C_Slider_CallBack(this, &C_Slider_CallBack_Func),
		Object(NULL)
	{
		float x = 0;
		float y = 0;

		T_Slider.Anchor.X.Anchor = ANCHOR_MIN;
		T_Slider.Anchor.Y.Anchor = ANCHOR_MIN;
		T_Slider.Anchor.X.SetPaddedMinDist(0);
		T_Slider.Anchor.Y.SetPaddedMinDist(y);

		x = T_Slider.Anchor.X.GetPaddedMinSize();

		T_Text.Anchor.X.Anchor = ANCHOR_BOTH;
		T_Text.Anchor.Y.Anchor = ANCHOR_MIN;
		T_Text.Anchor.X.SetPaddedMinDist(x);
		T_Text.Anchor.X.SetPaddedMaxDist(0);
		T_Text.Anchor.Y.SetPaddedMinDist(y);

		y = T_Slider.Anchor.Y.GetPaddedMinSize();

		B_Slider.Anchor.X.Anchor = ANCHOR_MIN;
		B_Slider.Anchor.Y.Anchor = ANCHOR_MIN;
		B_Slider.Anchor.X.SetPaddedMinDist(0);
		B_Slider.Anchor.Y.SetPaddedMinDist(y);

		x = B_Slider.Anchor.X.GetPaddedMinSize();

		B_Text.Anchor.X.Anchor = ANCHOR_BOTH;
		B_Text.Anchor.Y.Anchor = ANCHOR_MIN;
		B_Text.Anchor.X.SetPaddedMinDist(x);
		B_Text.Anchor.X.SetPaddedMaxDist(0);
		B_Text.Anchor.Y.SetPaddedMinDist(y);

		y = B_Slider.Anchor.Y.GetPaddedMinSize();

		C_Slider.Anchor.X.Anchor = ANCHOR_MIN;
		C_Slider.Anchor.Y.Anchor = ANCHOR_MIN;
		C_Slider.Anchor.X.SetPaddedMinDist(0);
		C_Slider.Anchor.Y.SetPaddedMinDist(y);

		x = C_Slider.Anchor.X.GetPaddedMinSize();

		C_Text.Anchor.X.Anchor = ANCHOR_BOTH;
		C_Text.Anchor.Y.Anchor = ANCHOR_MIN;
		C_Text.Anchor.X.SetPaddedMinDist(x);
		C_Text.Anchor.X.SetPaddedMaxDist(0);
		C_Text.Anchor.Y.SetPaddedMinDist(y);

		y = C_Slider.Anchor.Y.GetPaddedMinSize();

		ChildInsert(&T_Slider);
		ChildInsert(&T_Text);
		ChildInsert(&B_Slider);
		ChildInsert(&B_Text);
		ChildInsert(&C_Slider);
		ChildInsert(&C_Text);

		Anchor.X.Anchor = ANCHOR_MIN;
		Anchor.Y.Anchor = ANCHOR_MIN;
		Anchor.X.SetPaddedMinDist(0);
		Anchor.Y.SetPaddedMinDist(0);
		Anchor.X.SetSize(240);
		Anchor.Y.SetSize((25 + 5 * 2) * 3);
	}
	~SplineSegment3D()
	{ }

	/*
		if obj != NULL
			change Sliders and Text based on Object
		if obj == NULL
			disable
			maybe change Sliders and Text to Default
	*/
	void ChangeObject(::SplineSegment3D * obj)
	{
		(void)obj;
	}

	private:
	void T_Slider_CallBack_Func()
	{

	}
	void B_Slider_CallBack_Func()
	{

	}
	void C_Slider_CallBack_Func()
	{

	}
};
};
};

#endif