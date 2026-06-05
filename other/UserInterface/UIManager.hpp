#ifndef  UI_MANAGER_HPP
# define UI_MANAGER_HPP

# include "Control/Base/Manager.hpp"
# include "Text/Manager.hpp"

# include "Display/DisplaySize.hpp"
# include "Control/Window.hpp"

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
	// Graph Manager



	DisplaySize				WindowSize;
	UI::Control::Window		WindowControl;



	Control::Base *		Hovering;
	Control::Base *		Selected;

	//Form *	BoxChanging;



	public:
	VectorF2		CursorPosition;

	GLFWwindow *	glfw_window;

	// put these in MouseManager ?
	GLFWcursor *	glfw_cursorArrowC;
	GLFWcursor *	glfw_cursorArrowH;
	GLFWcursor *	glfw_cursorArrowV;
	GLFWcursor *	glfw_cursorArrowD0;
	GLFWcursor *	glfw_cursorArrowD1;
	GLFWcursor *	glfw_cursorBoxEdge[4];
	GLFWcursor *	glfw_cursorBoxCorn[4];

	void	CursorsCreate(const DirectoryInfo & dir, GLFWwindow * glfw_window);
	void	CursorsDelete();

	void	CursorsUseDefault();
	void	CursorsUseArrowC();
	void	CursorsUseArrowH();
	void	CursorsUseArrowV();
	void	CursorsUseArrowD0();
	void	CursorsUseArrowD1();
	void	CursorsUseBoxEdge(unsigned char i);
	void	CursorsUseBoxCorn(unsigned char i);



	public:
	~Manager();
	Manager();
	Manager(const Manager & other) = delete;
	Manager & operator=(const Manager & other) = delete;



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

	public:
	void	ChangeMedia(const DirectoryInfo & dir, GLFWwindow * glfw_window);

	//private:
	//bool	GraphicsExist;
	public:
	void	GraphicsCreate();
	void	GraphicsDelete();

	public:
	void	Draw();
};

};

#endif