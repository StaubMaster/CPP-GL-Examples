#include "User/Args/ClickArgs.hpp"



ClickArgs::ClickArgs(int mods, int action, int button, DisplayPosition position)
	: Mods((::Modifier)mods)
	, Action((::Action)action)
	, Button((::MouseButtons)button)
	, Position(position)
{ }
