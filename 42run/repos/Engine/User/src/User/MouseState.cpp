#include "User/MouseState.hpp"



/*struct MouseState
{
	::MouseButtons	MouseButton;
	::State			State;

	DisplayPosition	LastPressPosition;
	DisplayPosition	LastReleasePosition;

	void	Update(DisplayPosition pos, Action action);
};*/
MouseState::MouseState(::MouseButtons button)
	: Button(button)
	, State(::State::Up)
	, IsDragging(false)
{ }



void MouseState::Tick()
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
void MouseState::Update(DisplayPosition pos, Action action)
{
	if (action == Action::Press)
	{
		LastPressPosition = pos;
		State = State::Press;
	}
	if (action == Action::Release)
	{
		LastReleasePosition = pos;
		State = State::Release;
	}
}



bool MouseState::operator==(::MouseButtons button) const { return (Button == button); }
bool MouseState::operator!=(::MouseButtons button) const { return (Button != button); }
bool MouseState::operator==(::State state) const { return (State == state); }
bool MouseState::operator!=(::State state) const { return (State == state); }



bool MouseState::IsUp() const		{ return (State == State::Up); }
bool MouseState::IsDown() const		{ return (State == State::Down); }
bool MouseState::IsPress() const	{ return (State == State::Press); }
bool MouseState::IsRelease() const	{ return (State == State::Release); }
