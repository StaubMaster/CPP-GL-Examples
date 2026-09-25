#ifndef  USER_KEY_STATE_HPP
# define USER_KEY_STATE_HPP

# include "User/Enums/Keys.hpp"
# include "User/Enums/State.hpp"
# include "User/Enums/Action.hpp"

struct KeyState
{
	::Keys	Key;
	::State	State;

	KeyState(::Keys key);

	void	Tick();
	void	Update(Action action);

	bool	operator==(::Keys key) const;
	bool	operator!=(::Keys key) const;
	bool	operator==(::State state) const;
	bool	operator!=(::State state) const;
};

#endif