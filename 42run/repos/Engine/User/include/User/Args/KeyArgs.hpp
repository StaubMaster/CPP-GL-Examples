#ifndef  USER_ARGS_KEY_HPP
# define USER_ARGS_KEY_HPP

# include "User/Enums/Keys.hpp"
# include "User/Enums/Action.hpp"
# include "User/Enums/Modifier.hpp"

struct KeyArgs
{
	::Modifier	Mods;
	::Action	Action;
	::Keys		Key;
	int			Scancode;

	KeyArgs(int keycode, int scancode, int action, int mods);
};

#endif