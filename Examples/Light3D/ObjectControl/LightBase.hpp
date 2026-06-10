#ifndef  OBJECT_CONTROL_LIGHT_BASE_HPP
# define OBJECT_CONTROL_LIGHT_BASE_HPP

# include "Control/GroupBox.hpp"
# include "Control/Label.hpp"
# include "ObjectControl/ColorF4.hpp"

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