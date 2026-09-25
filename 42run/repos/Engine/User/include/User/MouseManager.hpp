#ifndef  USER_MOUSE_MANAGER_HPP
# define USER_MOUSE_MANAGER_HPP

# include "User/MouseState.hpp"

# include "User/Args/ClickArgs.hpp"
# include "User/Args/DragArgs.hpp"
# include "User/Args/MoveArgs.hpp"
# include "User/Args/ScrollArgs.hpp"

# include "Generics/Function/Pointer.hpp"

class Window;

struct MouseManager
{
	private:
	static const unsigned int StateNum = 8;

	private:
	Window & window;
	MouseState MouseStates[StateNum];

	public:
	const MouseState & operator[](const MouseButtons & button) const;

	public:
	FunctionPointer<ClickArgs>		Callback_ClickEvent;
	FunctionPointer<MoveArgs>		Callback_MoveEvent;
	FunctionPointer<DragArgs>		Callback_DragEvent;
	FunctionPointer<ScrollArgs>		Callback_ScrollEvent;

	public:
	~MouseManager();
	MouseManager(Window & win);
	MouseManager(const MouseManager & other) = delete;
	MouseManager & operator=(const MouseManager & other) = delete;

	public:
	bool	CursorModeIsLocked() const;
	void	CursorModeLock();
	void	CursorModeFree();
	void	CursorModeToggle();
	
	DisplayPosition	CursorPosition() const;
	void			CursorPositionTick();

	public:
	void	Tick();
	void	Update(MouseButtons button, Action action);

	public:
	void	Invoke_ClickEvent(int button, int action, int mods);
	void	Invoke_ScrollEvent(float offset_x, float offset_y);
	void	Invoke_MoveEvent(double x_pos, double y_pos);
};

#endif