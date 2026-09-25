#include "User/Enums/Keys.hpp"

#include <iostream>
std::ostream & operator<<(std::ostream & s, const Keys & val)
{
	switch (val)
	{
		case Keys::Space: s << "Space"; break;

		case Keys::D0: s << "D0"; break;
		case Keys::D1: s << "D1"; break;
		case Keys::D2: s << "D2"; break;
		case Keys::D3: s << "D3"; break;
		case Keys::D4: s << "D4"; break;
		case Keys::D5: s << "D5"; break;
		case Keys::D6: s << "D6"; break;
		case Keys::D7: s << "D7"; break;
		case Keys::D8: s << "D8"; break;
		case Keys::D9: s << "D9"; break;

		case Keys::A: s << "A"; break;
		case Keys::B: s << "B"; break;
		case Keys::C: s << "C"; break;
		case Keys::D: s << "D"; break;
		case Keys::E: s << "E"; break;
		case Keys::F: s << "F"; break;
		case Keys::G: s << "G"; break;
		case Keys::H: s << "H"; break;
		case Keys::I: s << "I"; break;
		case Keys::J: s << "J"; break;
		case Keys::K: s << "K"; break;
		case Keys::L: s << "L"; break;
		case Keys::M: s << "M"; break;
		case Keys::N: s << "N"; break;
		case Keys::O: s << "O"; break;
		case Keys::P: s << "P"; break;
		case Keys::Q: s << "Q"; break;
		case Keys::R: s << "R"; break;
		case Keys::S: s << "S"; break;
		case Keys::T: s << "T"; break;
		case Keys::U: s << "U"; break;
		case Keys::V: s << "V"; break;
		case Keys::W: s << "W"; break;
		case Keys::X: s << "X"; break;
		case Keys::Y: s << "Y"; break;
		case Keys::Z: s << "Z"; break;

		case Keys::Escape: s << "Escape"; break;
		case Keys::Enter: s << "Enter"; break;
		case Keys::Tab: s << "Tab"; break;
		case Keys::Backspace: s << "Backspace"; break;
		case Keys::Insert: s << "Insert"; break;
		case Keys::Delete: s << "Delete"; break;
		case Keys::Right: s << "Right"; break;
		case Keys::Left: s << "Left"; break;
		case Keys::Down: s << "Down"; break;
		case Keys::Up: s << "Up"; break;
		case Keys::PageUp: s << "PageUp"; break;
		case Keys::PageDown: s << "PageDown"; break;
		case Keys::Home: s << "Home"; break;
		case Keys::End: s << "End"; break;

		case Keys::F1: s << "F1"; break;
		case Keys::F2: s << "F2"; break;
		case Keys::F3: s << "F3"; break;
		case Keys::F4: s << "F4"; break;
		case Keys::F5: s << "F5"; break;
		case Keys::F6: s << "F6"; break;
		case Keys::F7: s << "F7"; break;
		case Keys::F8: s << "F8"; break;
		case Keys::F9: s << "F9"; break;
		case Keys::F10: s << "F10"; break;
		case Keys::F11: s << "F11"; break;
		case Keys::F12: s << "F12"; break;
		case Keys::F13: s << "F13"; break;
		case Keys::F14: s << "F14"; break;
		case Keys::F15: s << "F15"; break;
		case Keys::F16: s << "F16"; break;
		case Keys::F17: s << "F17"; break;
		case Keys::F18: s << "F18"; break;
		case Keys::F19: s << "F19"; break;
		case Keys::F20: s << "F20"; break;
		case Keys::F21: s << "F21"; break;
		case Keys::F22: s << "F22"; break;
		case Keys::F23: s << "F23"; break;
		case Keys::F24: s << "F24"; break;
		case Keys::F25: s << "F25"; break;

		case Keys::NumPad0: s << "NumPad0"; break;
		case Keys::NumPad1: s << "NumPad1"; break;
		case Keys::NumPad2: s << "NumPad2"; break;
		case Keys::NumPad3: s << "NumPad3"; break;
		case Keys::NumPad4: s << "NumPad4"; break;
		case Keys::NumPad5: s << "NumPad5"; break;
		case Keys::NumPad6: s << "NumPad6"; break;
		case Keys::NumPad7: s << "NumPad7"; break;
		case Keys::NumPad8: s << "NumPad8"; break;
		case Keys::NumPad9: s << "NumPad9"; break;
		case Keys::NumPadDecimal: s << "NumPadDecimal"; break;
		case Keys::NumPadAdd: s << "NumPadAdd"; break;
		case Keys::NumPadSub: s << "NumPadSub"; break;
		case Keys::NumPadMul: s << "NumPadMul"; break;
		case Keys::NumPadDiv: s << "NumPadDiv"; break;
		case Keys::NumPadEnter: s << "NumPadEnter"; break;
		case Keys::NumPadEqual: s << "NumPadEqual"; break;

		case Keys::LeftShift: s << "LeftShift"; break;
		case Keys::LeftControl: s << "LeftControl"; break;
		case Keys::LeftAlt: s << "LeftAlt"; break;
		case Keys::LeftSuper: s << "LeftSuper"; break;
		case Keys::RightShift: s << "RightShift"; break;
		case Keys::RightControl: s << "RightControl"; break;
		case Keys::RightAlt: s << "RightAlt"; break;
		case Keys::RightSuper: s << "RightSuper"; break;
		case Keys::Menu: s << "Menu"; break;

		default: s << "Keys: " << ((unsigned int)val);
	}
	return s;
}
