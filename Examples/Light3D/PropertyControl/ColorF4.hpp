#ifndef  PROPERTY_CONTROL_COLOR_F_4_HPP
# define PROPERTY_CONTROL_COLOR_F_4_HPP

# include "PropertyControl.hpp"
# include "Control/Label.hpp"

struct ColorF4;

namespace UI
{
namespace Control
{
struct ColorF4 : public PropertyControl
{
	Label	R;
	Label	G;
	Label	B;
	// A ?

	~ColorF4();
	ColorF4(const char * name);

	::ColorF4 * Object;
	void	Change(::ColorF4 * obj);
};
};
};

#endif