#ifndef  UI_NESTED_PROPERTY_HPP
# define UI_NESTED_PROPERTY_HPP

# include "Control/Controls/GroupBox.hpp"
# include "Control/Controls/Button.hpp"

namespace UI
{
struct NestedProperty : public UI::Control_::GroupBox
{
	UI::Control_::Button	Toggle;

	public:
	NestedProperty(const char * name);

	private:
	bool	Expanded = true;
	public:
	void	Maximize();
	void	Minimize();
	void	ExpansionChanged();

	public:
	void	ToggleFunc(ClickArgs args);

	public:
	virtual void	Syncronize() = 0;
};
};

#endif