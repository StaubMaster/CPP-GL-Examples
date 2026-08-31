#ifndef  UI_MANAGER_HPP
# define UI_MANAGER_HPP

# include "Control/General/Manager.hpp"
# include "Text/Manager.hpp"
# include "Graph/Manager.hpp"

# include "Display/DisplaySize.hpp"
# include "Control/Window.hpp"

# include "CursorManager.hpp"

namespace UI
{

namespace Control
{
class Base;
};

class Manager
{
	public:
	Control::Manager	ControlManager;
	Text::Manager		TextManager;
	Graph::Manager		GraphManager;



	DisplaySize				WindowSize;
	UI::Control::Window		WindowControl;



	Control::Base *		Hovering;
	Control::Base *		Selected;

	//Form *	BoxChanging;



	public:
	~Manager();
	Manager();
	Manager(const Manager & other) = delete;
	Manager & operator=(const Manager & other) = delete;

	public:
	CursorManager	Cursor;

	public:
	void	MouseMove(MoveArgs args);
	void	MouseClick(ClickArgs args);
	void	MouseScroll(ScrollArgs args);
	void	MouseDrag(DragArgs args);
	void	KeyBoardKey(KeyArgs args);
	void	KeyBoardText(TextArgs args);

	public:
	void	UpdateMouse(DisplayPosition mouse_pos);
	void	Resize(DisplaySize display_size);
	void	Update();

	public:
	void	ChangeMedia(const DirectoryInfo & dir, GLFWwindow * glfw_window);

	//private:
	//bool	GraphicsExist;

	public:
	void	GraphicsCreate();
	void	GraphicsDelete();
	void	GraphicsInit();

	public:
	void	GraphicsMake();
	void	GraphicsDraw();
};

};

#endif