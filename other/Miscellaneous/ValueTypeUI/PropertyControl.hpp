#ifndef  PROPERTY_CONTROL_HPP
# define PROPERTY_CONTROL_HPP

# include "Control/Controls/GroupBox.hpp"
# include "Control/Controls/Button.hpp"

namespace UI
{
namespace Control_
{
struct PropertyControl : public GroupBox
{
	Button	Toggle;

	public:
	PropertyControl(const char * name);

	private:
	bool	Expanded = true;
	public:
	void	Maximize();
	void	Minimize();
	void	ExpansionChanged();

	public:
	void	ToggleFunc(ClickArgs args);
};
};
};

#endif