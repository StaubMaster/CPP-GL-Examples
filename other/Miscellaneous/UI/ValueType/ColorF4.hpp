#ifndef  PROPERTY_CONTROL_COLOR_F_4_HPP
# define PROPERTY_CONTROL_COLOR_F_4_HPP

# include "UI/NestedProperty.hpp"
# include "Control/Controls/Slider.hpp"

struct ColorF4;

namespace UI
{
struct ColorF4 : public NestedProperty
{
	UI::Control_::Slider	R;
	UI::Control_::Slider	G;
	UI::Control_::Slider	B;
	// A ?

	ColorF4(const char * name);

	::ColorF4 * Object;
	void	Syncronize();
	void	Change(::ColorF4 * obj);

	void	RFunc(float val);
	void	GFunc(float val);
	void	BFunc(float val);
};
};

#endif