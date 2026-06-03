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



namespace UI
{

namespace Control
{
class Base;

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

	public:
	// Cursors
	VectorF2		CursorPosition;
	GLFWwindow *	glfw_window;
	GLFWcursor *	glfw_cursorResizeH;
	GLFWcursor *	glfw_cursorResizeV;
	GLFWcursor *	glfw_cursorResizeD0;
	GLFWcursor *	glfw_cursorResizeD1;
	GLFWcursor *	glfw_cursorCross;
	void	CursorsCreate();
	void	CursorsDelete();
	void	CursorsUseDefault();
	void	CursorsUseResizeH();
	void	CursorsUseResizeV();
	void	CursorsUseResizeD0();
	void	CursorsUseResizeD1();
	void	CursorsUseCross();

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

	private:
	bool	GraphicsExist;
	public:
	void	GraphicsCreate();
	void	GraphicsDelete();

	private:
	bool	GraphicsNeedInit;
	bool	GraphicsNeedMain;
	private:
	void	GraphicsInit();
	void	GraphicsMain();
	void	GraphicsInst();

	private:
	void	PlaceInstance(const ObjectData & obj);

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