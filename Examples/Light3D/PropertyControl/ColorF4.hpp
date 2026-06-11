#ifndef  PROPERTY_CONTROL_COLOR_F_4_HPP
# define PROPERTY_CONTROL_COLOR_F_4_HPP

# include "PropertyControl.hpp"
# include "Control/Slider.hpp"

struct ColorF4;

namespace UI
{
namespace Control
{
struct ColorF4 : public PropertyControl
{
	Slider	R;
	Slider	G;
	Slider	B;
	// A ?

	~ColorF4();
	ColorF4(const char * name);

	::ColorF4 * Object;
	void	Change(::ColorF4 * obj);

	void	RFunc(float val);
	void	GFunc(float val);
	void	BFunc(float val);
};
};
};

#endif