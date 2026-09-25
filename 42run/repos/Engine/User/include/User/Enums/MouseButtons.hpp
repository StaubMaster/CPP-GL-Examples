#ifndef  USER_MOUSE_BUTTONS_HPP
# define USER_MOUSE_BUTTONS_HPP

# include "OpenGL.hpp"

enum class MouseButtons : unsigned int
{

Mouse1 = GLFW_MOUSE_BUTTON_1,
Mouse2 = GLFW_MOUSE_BUTTON_2,
Mouse3 = GLFW_MOUSE_BUTTON_3,
Mouse4 = GLFW_MOUSE_BUTTON_4,
Mouse5 = GLFW_MOUSE_BUTTON_5,
Mouse6 = GLFW_MOUSE_BUTTON_6,
Mouse7 = GLFW_MOUSE_BUTTON_7,
Mouse8 = GLFW_MOUSE_BUTTON_8,
// 8

MouseL = GLFW_MOUSE_BUTTON_LEFT,	// 1
MouseR = GLFW_MOUSE_BUTTON_RIGHT,	// 2
MouseM = GLFW_MOUSE_BUTTON_MIDDLE,	// 3
};

#include <iosfwd>
std::ostream & operator<<(std::ostream & s, const MouseButtons & val);

#endif