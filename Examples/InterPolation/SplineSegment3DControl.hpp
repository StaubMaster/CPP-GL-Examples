#ifndef  SPLINE_SEGMENT_3D_CONTROL_HPP
# define SPLINE_SEGMENT_3D_CONTROL_HPP

# include "SplineSegment3D.hpp"
# include "CubicSpline3D.hpp"

# include "ControlsInclude.hpp"
# include "User/MouseArgs.hpp"
# include "Miscellaneous/Function/Object.hpp"

namespace UI
{
namespace Control
{
class SplineSegment3D : public GroupBox
{
	private:
	Slider	T_Slider;
	Slider	C_Slider;
	Slider	B_Slider;

	TextBox	T_Text;
	TextBox	C_Text;
	TextBox	B_Text;

	Button	Prev_Button;
	Button	Next_Button;

	TextBox	Prev_Text;
	TextBox	Next_Text;

	private:
//	::SplineSegment3D * Object;
	::CubicSpline3D::FactorsTCB * TCB;

	public:
	SplineSegment3D();
	~SplineSegment3D();

	//void ChangeObject(::SplineSegment3D * obj);
	void ChangeObject(::CubicSpline3D::FactorsTCB * obj);

	private:
	void T_Slider_CallBack_Func(float val);
	void B_Slider_CallBack_Func(float val);
	void C_Slider_CallBack_Func(float val);
	void Prev_Button_CallBack_Func(ClickArgs params);
	void Next_Button_CallBack_Func(ClickArgs params);
};
};
};

#endif