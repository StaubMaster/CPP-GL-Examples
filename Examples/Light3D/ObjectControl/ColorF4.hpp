#ifndef  OBJECT_CONTROL_COLOR_F_4_HPP
# define OBJECT_CONTROL_COLOR_F_4_HPP

# include "Control/GroupBox.hpp"
# include "Control/Label.hpp"

struct ColorF4;

namespace UI
{
namespace Control
{
struct ColorF4 : public GroupBox
{
	Label	R;
	Label	G;
	Label	B;
	// A ?

	~ColorF4();
	ColorF4();

	::ColorF4 * Object;
	void	Change(::ColorF4 * obj);
};
};
};

#endif