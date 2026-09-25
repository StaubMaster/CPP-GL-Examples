#ifndef  USER_ACTION_HPP
# define USER_ACTION_HPP

# include "OpenGL.hpp"

enum class Action : unsigned int
{
	Press = GLFW_PRESS,
	Repeat = GLFW_REPEAT,
	Release = GLFW_RELEASE,
};

#include <iosfwd>
std::ostream & operator<<(std::ostream & s, const Action & val);

#endif