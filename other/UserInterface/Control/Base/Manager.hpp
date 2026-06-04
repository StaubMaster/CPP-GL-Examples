#ifndef  UI_CONTROL_MANAGER_HPP
# define UI_CONTROL_MANAGER_HPP

# include "Data.hpp"
# include "Buffer.hpp"
# include "ShaderLayout.hpp"
# include "Graphics/Shader/Base.hpp"

# include "Control/Window.hpp"

# include "Display/DisplaySize.hpp"

# include "User/MouseArgs.hpp"
# include "User/KeyBoardArgs.hpp"

# include "Miscellaneous/Container/Binary.hpp"

# include "OpenGL.hpp"



class DirectoryInfo;

namespace UI
{

namespace Control
{
class Base;
class Form;

struct ObjectData;

class Manager
{
	public:
	static Manager * CurrentPointer;
	static Manager & Current();
	static bool CheckCurrent();
	static void ClearCurrent();
	bool IsCurrent() const;
	void MakeCurrent();





	public:
	::Shader::Base					Shader;
	UI::Control::ShaderLayout		ShaderLayout;

	UI::Control::Buffer				Buffer;
	UI::Control::Main_Layout		BufferLayoutMain;
	UI::Control::Inst_Layout		BufferLayoutInst;

	Container::Binary<ObjectData*>			ObjectDatas;
	Container::Binary<Control::Inst_Data>	Instances;

	DisplaySize				WindowSize;
	UI::Control::Window		WindowControl;

	Base *	Hovering;
	Base *	Selected;

	Form *	BoxChanging;

	// Cursors
	public:
	VectorF2		CursorPosition;

	GLFWwindow *	glfw_window;
	GLFWcursor *	glfw_cursorArrowC;
	GLFWcursor *	glfw_cursorArrowH;
	GLFWcursor *	glfw_cursorArrowV;
	GLFWcursor *	glfw_cursorArrowD0;
	GLFWcursor *	glfw_cursorArrowD1;
	GLFWcursor *	glfw_cursorBoxEdge[4];
	GLFWcursor *	glfw_cursorBoxCorn[4];

	void	CursorsCreate(const DirectoryInfo & dir);
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
	Manager(GLFWwindow * glfw_window);
	Manager(const Manager & other) = delete;
	Manager & operator=(const Manager & other) = delete;

	public:
	ObjectData *	PlaceObject();
	ObjectData *	CopyObject(const ObjectData * obj);
	// give these functions static Variants that return if no Current
	// else they do the stuff with current

	public:
	void	ChangeMedia(const DirectoryInfo & dir);

	private:
	bool	GraphicsExist;
	public:
	void	GraphicsCreate();
	void	GraphicsDelete();

	private:
	bool	GraphicsNeedMain;

	private:
	void	GraphicsMain();
	void	GraphicsInst();

	private:
	void	PlaceInstance(const ObjectData & obj);
	void	MakeInstances();

	public:
	void	Draw();
	
	void	UpdateSize(const DisplaySize & window_size);
	void	UpdateMouse(VectorF2 mouse);

	public:
	void	RelayClick(ClickArgs args);
	void	RelayScroll(ScrollArgs args);
	void	RelayCursorDrag(DragArgs args);

	void	RelayKey(KeyArgs args);
	void	RelayText(TextArgs args);
};

};

};

#endif