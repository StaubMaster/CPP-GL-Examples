#ifndef  PROPERTY_CONTROL_LIGHT_BASE_HPP
# define PROPERTY_CONTROL_LIGHT_BASE_HPP

# include "PropertyControl.hpp"
# include "ValueTypeUI/ColorF4.hpp"
# include "Control/Slider.hpp"

struct LightBase;

namespace UI
{
namespace Control
{
struct LightBase : public PropertyControl
{
	Slider		Intensity;
	ColorF4		Color;

	~LightBase();
	LightBase(const char * name);

	::LightBase * Object;
	void	Update();
	void	Change(::LightBase * obj);

	void	IntensityFunc(float val);
};
};
};

#endif