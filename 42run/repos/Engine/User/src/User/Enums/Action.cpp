#include "User/Enums/Action.hpp"

#include <iostream>
std::ostream & operator<<(std::ostream & s, const Action & val)
{
	switch (val)
	{
		case Action::Press: s << "Press"; break;
		case Action::Repeat: s << "Repeat"; break;
		case Action::Release: s << "Release"; break;

		default: s << "Action: " << ((unsigned int)val);
	}
	return s;
}
