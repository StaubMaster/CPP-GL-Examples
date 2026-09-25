#ifndef  USER_MODIFIER_HPP
# define USER_MODIFIER_HPP

# include "OpenGL.hpp"

enum class Modifier : unsigned int
{
	None = 0,
	Shift = GLFW_MOD_SHIFT,
	Control = GLFW_MOD_CONTROL,
	Alt = GLFW_MOD_ALT,
	Super = GLFW_MOD_SUPER,
	CapsLock = GLFW_MOD_CAPS_LOCK,
	NumLock = GLFW_MOD_NUM_LOCK,
	ScrollLock = GLFW_KEY_SCROLL_LOCK,
};

Modifier operator|(const Modifier & val0, const Modifier & val1);
Modifier operator&(const Modifier & val0, const Modifier & val1);

#include <iosfwd>
std::ostream & operator<<(std::ostream & s, const Modifier & val);

#endif