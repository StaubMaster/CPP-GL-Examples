#include "User/Enums/Modifier.hpp"

/*
	Shift		GLFW_MOD_SHIFT			0x0001	'S'
	Control		GLFW_MOD_CONTROL		0x0002	'C'
	Alt			GLFW_MOD_ALT			0x0008	'A'
	Super		GLFW_MOD_SUPER			0x0008	'A'
	CapsLock	GLFW_MOD_CAPS_LOCK		0x0010	'c'
	NumLock		GLFW_MOD_NUM_LOCK		0x0020	'n'
	ScrollLock	GLFW_KEY_SCROLL_LOCK	
*/

Modifier operator|(const Modifier & val0, const Modifier & val1) { return (Modifier)(((unsigned int)val0) | ((unsigned int)val1)); }
Modifier operator&(const Modifier & val0, const Modifier & val1) { return (Modifier)(((unsigned int)val0) & ((unsigned int)val1)); }

#include <iostream>
std::ostream & operator<<(std::ostream & s, const Modifier & val)
{
	s << "Modifier: " << ((unsigned int)val);
	return s;
}
