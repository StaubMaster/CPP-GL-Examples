#ifndef  USER_ARGS_DRAG_HPP
# define USER_ARGS_DRAG_HPP

# include "User/Enums/MouseButtons.hpp"
# include "User/Enums/Action.hpp"
# include "User/Enums/Modifier.hpp"

# include "Display/DisplayPosition.hpp"

struct DragArgs
{
	::Modifier			Mods;
	/* Action does not refer to MouseButton
		Press: start of Drag
		Repeat: Drag movement
		Release: end of Drag
	*/
	::Action			Action;
	::MouseButtons		Button;

	DisplayPosition		Position;

	DragArgs(::Modifier mods, ::Action action, ::MouseButtons button, DisplayPosition pos);
};

#endif