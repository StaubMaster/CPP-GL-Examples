#include "User/Enums/MouseButtons.hpp"

#include <iostream>
std::ostream & operator<<(std::ostream & s, const MouseButtons & val)
{
	switch (val)
	{
		//case MouseButtons::Mouse1: s << "Mouse1"; break;
		//case MouseButtons::Mouse2: s << "Mouse2"; break;
		//case MouseButtons::Mouse3: s << "Mouse3"; break;
		case MouseButtons::Mouse4: s << "Mouse4"; break;
		case MouseButtons::Mouse5: s << "Mouse5"; break;
		case MouseButtons::Mouse6: s << "Mouse6"; break;
		case MouseButtons::Mouse7: s << "Mouse7"; break;
		case MouseButtons::Mouse8: s << "Mouse8"; break;

		case MouseButtons::MouseL: s << "MouseL"; break;
		case MouseButtons::MouseR: s << "MouseR"; break;
		case MouseButtons::MouseM: s << "MouseM"; break;

		default: s << "MouseButtons: " << ((unsigned int)val);
	}
	return s;
}
