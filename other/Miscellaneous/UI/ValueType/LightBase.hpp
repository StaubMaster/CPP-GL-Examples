#ifndef  PROPERTY_CONTROL_LIGHT_BASE_HPP
# define PROPERTY_CONTROL_LIGHT_BASE_HPP

# include "UI/NestedProperty.hpp"
# include "UI/ValueType/ColorF4.hpp"
# include "Control/Controls/Slider.hpp"

struct LightBase;

namespace UI
{
struct LightBase : public NestedProperty
{
	UI::Control_::Slider		Intensity;
	ColorF4						Color;

	LightBase(const char * name);

	::LightBase * Object;
	void	Syncronize();
	void	Change(::LightBase * obj);

	void	IntensityFunc(float val);
};
};

#endif