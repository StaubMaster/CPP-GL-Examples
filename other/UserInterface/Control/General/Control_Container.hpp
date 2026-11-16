#ifndef  UI_CONTROL_CONTROL_CONTAINER_HPP
# define UI_CONTROL_CONTROL_CONTAINER_HPP

# include "Generics/Container/Binary.hpp"

struct DisplayPosition;

namespace UI
{
class Control_Base;
class Control_Container
{
	public:
	Container::Binary<Control_Base*>	Children;

	public:
	virtual void	ChildClear();
	virtual void	ChildRemove(Control_Base & control);
	virtual void	ChildInsert(Control_Base & control);

	public:
	void	ChildRemove(Control_Base * control);
	void	ChildInsert(Control_Base * control);

	private:	virtual	bool			Check(const DisplayPosition & display_pos) const = 0;
	public:		virtual	Control_Base *	Find(const DisplayPosition & display_pos) = 0;



/* Recursive : Hovering & Selected

UpdateHovering()
{
	control = FindHovering()

	if (control == Hovering)
	{
		Hovering.Relay(Move)
	}
	else
	{
		Hovering.Relay(Leave) recursive
		Hovering = control
		Hovering.Relay(Enter)
	}

	control.UpdateHovering()
}

*/



	public:
	virtual ~Control_Container() = default;
	Control_Container() = default;
	Control_Container(const Control_Container & other) = delete;
	Control_Container & operator=(const Control_Container & other) = delete;
};
};

#endif