#ifndef  USER_ARGS_SCROLL_HPP
# define USER_ARGS_SCROLL_HPP

# include "User/Enums/Keys.hpp"
# include "User/Enums/Action.hpp"
# include "User/Enums/Modifier.hpp"

# include "Display/DisplayPosition.hpp"

struct ScrollArgs
{
	::Modifier			Mods;

	float				X;
	float				Y;
	DisplayPosition		Position;

	ScrollArgs(::Modifier mods, float x, float y, DisplayPosition position);
};

#endif