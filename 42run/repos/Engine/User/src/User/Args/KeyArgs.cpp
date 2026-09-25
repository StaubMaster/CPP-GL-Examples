#include "User/Args/KeyArgs.hpp"



KeyArgs::KeyArgs(int keycode, int scancode, int action, int mods)
	: Mods((::Modifier)mods)
	, Action((::Action)action)
	, Key((::Keys)keycode)
	, Scancode(scancode)
{ }
