#include "User/Args/DragArgs.hpp"



DragArgs::DragArgs(::Modifier mods, ::Action action, ::MouseButtons button, DisplayPosition pos)
	: Mods(mods)
	, Action(action)
	, Button(button)
	, Position(pos)
{ }
