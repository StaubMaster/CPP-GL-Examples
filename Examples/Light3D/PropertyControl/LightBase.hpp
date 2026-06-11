#ifndef  PROPERTY_CONTROL_LIGHT_BASE_HPP
# define PROPERTY_CONTROL_LIGHT_BASE_HPP

# include "Control/GroupBox.hpp"
# include "PropertyControl/ColorF4.hpp"
# include "Control/Label.hpp"

struct LightBase;

namespace UI
{
namespace Control
{
struct LightBase : public GroupBox
{
	Label		Intensity;
	ColorF4		Color;

	~LightBase();
	LightBase();

	::LightBase * Object;
	void	Change(::LightBase * obj);
};
};
};

#endif