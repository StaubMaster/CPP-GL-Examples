#ifndef  SPLINE_SEGMENT_3D_CONTROL_HPP
# define SPLINE_SEGMENT_3D_CONTROL_HPP

# include "Spline/SplineSegment3D.hpp"

# include "UI/ControlsInclude.hpp"
# include "UserParameter/MouseDeclare.hpp"
# include "Function/Object.hpp"

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
	::SplineSegment3D * Object;

	public:
	SplineSegment3D();
	~SplineSegment3D();

	void ChangeObject(::SplineSegment3D * obj);

	private:
	void T_Slider_CallBack_Func(float val);
	void B_Slider_CallBack_Func(float val);
	void C_Slider_CallBack_Func(float val);
	void Prev_Button_CallBack_Func(UserParameter::Mouse::Click params);
	void Next_Button_CallBack_Func(UserParameter::Mouse::Click params);
};
};
};

#endif