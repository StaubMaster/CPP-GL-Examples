#ifndef  UI_CURSOR_MANAGER_HPP
# define UI_CURSOR_MANAGER_HPP

# include "ValueType/Vector/F2.hpp"

# include "Control/Window.hpp"

class DirectoryInfo;

namespace UI
{
class CursorManager
{
	public:
	VectorF2		Position;

	GLFWwindow *	glfw_window;

	// make CursorManager ?
	// put these in MouseManager ?
	GLFWcursor *	glfw_cursorArrowC;
	GLFWcursor *	glfw_cursorArrowH;
	GLFWcursor *	glfw_cursorArrowV;
	GLFWcursor *	glfw_cursorArrowD0;
	GLFWcursor *	glfw_cursorArrowD1;
	GLFWcursor *	glfw_cursorBoxEdge[4];
	GLFWcursor *	glfw_cursorBoxCorn[4];

	~CursorManager();
	CursorManager();

	void	Create(const DirectoryInfo & dir, GLFWwindow * glfw_window);
	void	Delete();

	void	UseDefault();
	void	UseArrowC();
	void	UseArrowH();
	void	UseArrowV();
	void	UseArrowD0();
	void	UseArrowD1();
	void	UseBoxEdge(unsigned char i);
	void	UseBoxCorn(unsigned char i);
};
};

#endif