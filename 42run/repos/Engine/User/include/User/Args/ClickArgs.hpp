#ifndef  USER_ARGS_CLICK_HPP
# define USER_ARGS_CLICK_HPP

# include "User/Enums/MouseButtons.hpp"
# include "User/Enums/Action.hpp"
# include "User/Enums/Modifier.hpp"

# include "Display/DisplayPosition.hpp"

struct ClickArgs
{
	::Modifier			Mods;
	::Action			Action;
	::MouseButtons		Button;

	DisplayPosition		Position;

	ClickArgs(int mods, int action, int button, DisplayPosition position);
};

#endif