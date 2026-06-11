#ifndef  PROPERTY_CONTROL_HPP
# define PROPERTY_CONTROL_HPP

# include "Control/GroupBox.hpp"
# include "Control/Button.hpp"

namespace UI
{
namespace Control
{
struct PropertyControl : public GroupBox
{
	bool	Visible;
	Button	Toggle;

	~PropertyControl();
	PropertyControl(const char * name);

	void	ToggleFunc(ClickArgs args);
};
};
};

#endif