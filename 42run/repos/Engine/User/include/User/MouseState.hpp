#ifndef  USER_MOUSE_STATE_HPP
# define USER_MOUSE_STATE_HPP

# include "User/Enums/MouseButtons.hpp"
# include "User/Enums/State.hpp"
# include "User/Enums/Action.hpp"

# include "Display/DisplayPosition.hpp"

struct MouseState
{
	::MouseButtons	Button;
	::State			State;

	bool			IsDragging;
	DisplayPosition	LastPressPosition;
	DisplayPosition	LastReleasePosition;

	MouseState(::MouseButtons button);

	void	Tick();
	void	Update(DisplayPosition pos, Action action);

	bool	operator==(::MouseButtons button) const;
	bool	operator!=(::MouseButtons button) const;
	bool	operator==(::State state) const;
	bool	operator!=(::State state) const;

	bool	IsUp() const;
	bool	IsDown() const;
	bool	IsPress() const;
	bool	IsRelease() const;
};

#endif