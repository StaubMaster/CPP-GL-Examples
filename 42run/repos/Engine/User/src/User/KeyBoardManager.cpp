#include "User/KeyBoardManager.hpp"

#include "Window.hpp"
//#include <GLFW/glfw3.h>



const KeyState & KeyBoardManager::operator[](const Keys & key) const
{
	for (unsigned int i = 0; i < StateNum; i++)
	{
		if (KeyStates[i].Key == key)
		{
			return KeyStates[i];
		}
	}
	throw "KeyBoardManager[]: Key not found.";
}



KeyBoardManager::~KeyBoardManager() { }
KeyBoardManager::KeyBoardManager(Window & win)
	: window(win)
	, KeyStates{
		KeyState(Keys::Space),
		KeyState(Keys::D0),
		KeyState(Keys::D1),
		KeyState(Keys::D2),
		KeyState(Keys::D3),
		KeyState(Keys::D4),
		KeyState(Keys::D5),
		KeyState(Keys::D6),
		KeyState(Keys::D7),
		KeyState(Keys::D8),
		KeyState(Keys::D9),
		KeyState(Keys::A),
		KeyState(Keys::B),
		KeyState(Keys::C),
		KeyState(Keys::D),
		KeyState(Keys::E),
		KeyState(Keys::F),
		KeyState(Keys::G),
		KeyState(Keys::H),
		KeyState(Keys::I),
		KeyState(Keys::J),
		KeyState(Keys::K),
		KeyState(Keys::L),
		KeyState(Keys::M),
		KeyState(Keys::N),
		KeyState(Keys::O),
		KeyState(Keys::P),
		KeyState(Keys::Q),
		KeyState(Keys::R),
		KeyState(Keys::S),
		KeyState(Keys::T),
		KeyState(Keys::U),
		KeyState(Keys::V),
		KeyState(Keys::W),
		KeyState(Keys::X),
		KeyState(Keys::Y),
		KeyState(Keys::Z),
		KeyState(Keys::Escape),
		KeyState(Keys::Enter),
		KeyState(Keys::Tab),
		KeyState(Keys::Backspace),
		KeyState(Keys::Insert),
		KeyState(Keys::Delete),
		KeyState(Keys::Right),
		KeyState(Keys::Left),
		KeyState(Keys::Down),
		KeyState(Keys::Up),
		KeyState(Keys::PageUp),
		KeyState(Keys::PageDown),
		KeyState(Keys::Home),
		KeyState(Keys::End),
		KeyState(Keys::F1),
		KeyState(Keys::F2),
		KeyState(Keys::F3),
		KeyState(Keys::F4),
		KeyState(Keys::F5),
		KeyState(Keys::F6),
		KeyState(Keys::F7),
		KeyState(Keys::F8),
		KeyState(Keys::F9),
		KeyState(Keys::F10),
		KeyState(Keys::F11),
		KeyState(Keys::F12),
		KeyState(Keys::F13),
		KeyState(Keys::F14),
		KeyState(Keys::F15),
		KeyState(Keys::F16),
		KeyState(Keys::F17),
		KeyState(Keys::F18),
		KeyState(Keys::F19),
		KeyState(Keys::F20),
		KeyState(Keys::F21),
		KeyState(Keys::F22),
		KeyState(Keys::F23),
		KeyState(Keys::F24),
		KeyState(Keys::F25),
		KeyState(Keys::NumPad0),
		KeyState(Keys::NumPad1),
		KeyState(Keys::NumPad2),
		KeyState(Keys::NumPad3),
		KeyState(Keys::NumPad4),
		KeyState(Keys::NumPad5),
		KeyState(Keys::NumPad6),
		KeyState(Keys::NumPad7),
		KeyState(Keys::NumPad8),
		KeyState(Keys::NumPad9),
		KeyState(Keys::NumPadDecimal),
		KeyState(Keys::NumPadAdd),
		KeyState(Keys::NumPadSub),
		KeyState(Keys::NumPadMul),
		KeyState(Keys::NumPadDiv),
		KeyState(Keys::NumPadEnter),
		KeyState(Keys::NumPadEqual),
		KeyState(Keys::LeftShift),
		KeyState(Keys::LeftControl),
		KeyState(Keys::LeftAlt),
		KeyState(Keys::LeftSuper),
		KeyState(Keys::RightShift),
		KeyState(Keys::RightControl),
		KeyState(Keys::RightAlt),
		KeyState(Keys::RightSuper),
		KeyState(Keys::Menu),
	}
{ }



void KeyBoardManager::Tick()
{
	for (unsigned int i = 0; i < StateNum; i++)
	{
		KeyStates[i].Tick();
	}
}
void KeyBoardManager::Update(Keys key, Action action)
{
	for (unsigned int i = 0; i < StateNum; i++)
	{
		if (KeyStates[i].Key == key)
		{
			KeyStates[i].Update(action);
		}
	}
}



void KeyBoardManager::Invoke_KeyEvent(int key, int scancode, int action, int mods)
{
	Update((Keys)key, (Action)action);

	CallBack_KeyEvent.TryInvoke(KeyArgs(key, scancode, action, mods));
}
void KeyBoardManager::Invoke_TextEvent(unsigned int codepoint)
{
	CallBack_TextEvent.TryInvoke(TextArgs(codepoint));
}
