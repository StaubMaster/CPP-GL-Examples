#ifndef  USER_KEY_BOARD_MANAGER_HPP
# define USER_KEY_BOARD_MANAGER_HPP

# include "User/KeyState.hpp"

# include "User/Args/KeyArgs.hpp"
# include "User/Args/TextArgs.hpp"

# include "Generics/Function/Pointer.hpp"

class Window;

struct KeyBoardManager
{
	private:
	static const unsigned int StateNum = 102;

	private:
	Window & window;
	KeyState KeyStates[StateNum];

	public:
	const KeyState & operator[](const Keys & key) const;

	public:
	FunctionPointer<KeyArgs>		CallBack_KeyEvent;
	FunctionPointer<TextArgs>		CallBack_TextEvent;

	public:
	~KeyBoardManager();
	KeyBoardManager(Window & win);
	KeyBoardManager(const KeyBoardManager & other) = delete;
	KeyBoardManager & operator=(const KeyBoardManager & other) = delete;

	public:
	void	Tick();
	void	Update(Keys key, Action action);

	public:
	void	Invoke_KeyEvent(int key, int scancode, int action, int mods);
	void	Invoke_TextEvent(unsigned int codepoint);
};

#endif