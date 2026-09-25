#ifndef  USER_STATE_HPP
# define USER_STATE_HPP

# include "OpenGL.hpp"

// _x state
// x_ changed

enum class State : unsigned int
{
	Up = 0b00,
	Down = 0b01,
	Press = 0b11,
	Release = 0b10,
};

#include <iosfwd>
std::ostream & operator<<(std::ostream & s, const State & val);

#endif