#include "User/Enums/State.hpp"

#include <iostream>
std::ostream & operator<<(std::ostream & s, const State & val)
{
	switch (val)
	{
		case State::Up: s << "Up"; break;
		case State::Down: s << "Down"; break;
		case State::Press: s << "Press"; break;
		case State::Release: s << "Release"; break;

		default: s << "State: " << ((unsigned int)val);
	}
	return s;
}
