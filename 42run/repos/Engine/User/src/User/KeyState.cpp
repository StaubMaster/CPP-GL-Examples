#include "User/KeyState.hpp"

/*struct KeyState
{
	::Keys	Key;
	::State	State;
};*/

KeyState::KeyState(::Keys key)
	: Key(key)
	, State(::State::Up)
{ }



void KeyState::Tick()
{
	if (State == State::Press)
	{
		State = State::Down;
	}
	if (State == State::Release)
	{
		State = State::Up;
	}
}

void KeyState::Update(Action action)
{
	if (action == Action::Press)
	{
		State = State::Press;
	}
	if (action == Action::Release)
	{
		State = State::Release;
	}
}



bool KeyState::operator==(::Keys key) const { return (Key == key); }
bool KeyState::operator!=(::Keys key) const { return (Key != key); }
bool KeyState::operator==(::State state) const { return (State == state); }
bool KeyState::operator!=(::State state) const { return (State != state); }
