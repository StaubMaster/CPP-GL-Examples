#include "UIManager.hpp"

#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"





#include "Image.hpp"

static GLFWcursor * ImageToCursor(Image img)
{
	for (unsigned int i = 0; i < img.Size().Product(); i++)
	{
		ColorU4 & col = img.Pixel(i);
		if (col.R == 0x7F && col.G == 0x7F && col.B == 0x7F)
		{
			col.A = 0x00;
		}
	}

	GLFWimage glfw_img;
	glfw_img.width = img.W();
	glfw_img.height = img.H();
	glfw_img.pixels = (unsigned char *)img.Data();
	return glfwCreateCursor(&glfw_img, 15, 15);
}

void UI::Manager::CursorsCreate(const DirectoryInfo & dir, GLFWwindow * glfw_window)
{
	this -> glfw_window = glfw_window;

	glfw_cursorArrowC = ImageToCursor(dir.File("Images/Cursors/ArrowCross.png").LoadImage());

	glfw_cursorArrowH = ImageToCursor(dir.File("Images/Cursors/ArrowHori.png").LoadImage());
	glfw_cursorArrowV = ImageToCursor(dir.File("Images/Cursors/ArrowVert.png").LoadImage());
	glfw_cursorArrowD0 = ImageToCursor(dir.File("Images/Cursors/ArrowDiag0.png").LoadImage());
	glfw_cursorArrowD1 = ImageToCursor(dir.File("Images/Cursors/ArrowDiag1.png").LoadImage());

	glfw_cursorBoxEdge[0] = ImageToCursor(dir.File("Images/Cursors/BoxEdge0.png").LoadImage());
	glfw_cursorBoxEdge[1] = ImageToCursor(dir.File("Images/Cursors/BoxEdge1.png").LoadImage());
	glfw_cursorBoxEdge[2] = ImageToCursor(dir.File("Images/Cursors/BoxEdge2.png").LoadImage());
	glfw_cursorBoxEdge[3] = ImageToCursor(dir.File("Images/Cursors/BoxEdge3.png").LoadImage());

	glfw_cursorBoxCorn[0] = ImageToCursor(dir.File("Images/Cursors/BoxCorn0.png").LoadImage());
	glfw_cursorBoxCorn[1] = ImageToCursor(dir.File("Images/Cursors/BoxCorn1.png").LoadImage());
	glfw_cursorBoxCorn[2] = ImageToCursor(dir.File("Images/Cursors/BoxCorn2.png").LoadImage());
	glfw_cursorBoxCorn[3] = ImageToCursor(dir.File("Images/Cursors/BoxCorn3.png").LoadImage());
}
void UI::Manager::CursorsDelete()
{
	glfwDestroyCursor(glfw_cursorArrowC);

	glfwDestroyCursor(glfw_cursorArrowH);
	glfwDestroyCursor(glfw_cursorArrowV);
	glfwDestroyCursor(glfw_cursorArrowD0);
	glfwDestroyCursor(glfw_cursorArrowD1);

	glfwDestroyCursor(glfw_cursorBoxEdge[0]);
	glfwDestroyCursor(glfw_cursorBoxEdge[1]);
	glfwDestroyCursor(glfw_cursorBoxEdge[2]);
	glfwDestroyCursor(glfw_cursorBoxEdge[3]);

	glfwDestroyCursor(glfw_cursorBoxCorn[0]);
	glfwDestroyCursor(glfw_cursorBoxCorn[1]);
	glfwDestroyCursor(glfw_cursorBoxCorn[2]);
	glfwDestroyCursor(glfw_cursorBoxCorn[3]);
}

void UI::Manager::CursorsUseDefault() { if (glfw_window != nullptr) { glfwSetCursor(glfw_window, nullptr); } }
void UI::Manager::CursorsUseArrowC()  { if (glfw_window != nullptr) { glfwSetCursor(glfw_window, glfw_cursorArrowC); } }
void UI::Manager::CursorsUseArrowH()  { if (glfw_window != nullptr) { glfwSetCursor(glfw_window, glfw_cursorArrowH); } }
void UI::Manager::CursorsUseArrowV()  { if (glfw_window != nullptr) { glfwSetCursor(glfw_window, glfw_cursorArrowV); } }
void UI::Manager::CursorsUseArrowD0() { if (glfw_window != nullptr) { glfwSetCursor(glfw_window, glfw_cursorArrowD0); } }
void UI::Manager::CursorsUseArrowD1() { if (glfw_window != nullptr) { glfwSetCursor(glfw_window, glfw_cursorArrowD1); } }
void UI::Manager::CursorsUseBoxEdge(unsigned char i) { if (glfw_window != nullptr) { glfwSetCursor(glfw_window, glfw_cursorBoxEdge[i]); } }
void UI::Manager::CursorsUseBoxCorn(unsigned char i) { if (glfw_window != nullptr) { glfwSetCursor(glfw_window, glfw_cursorBoxCorn[i]); } }





UI::Manager::~Manager()
{ }
UI::Manager::Manager()
	: WindowSize()
	, WindowControl()
	, Hovering(nullptr)
	, Selected(nullptr)
	, glfw_window(nullptr)
	, glfw_cursorArrowC(nullptr)
	, glfw_cursorArrowH(nullptr)
	, glfw_cursorArrowV(nullptr)
	, glfw_cursorArrowD0(nullptr)
	, glfw_cursorArrowD1(nullptr)
	, glfw_cursorBoxEdge{ nullptr, nullptr, nullptr, nullptr }
	, glfw_cursorBoxCorn{ nullptr, nullptr, nullptr, nullptr }
{
	ControlManager.MakeCurrent();
	TextManager.MakeCurrent();
	GraphManager.MakeCurrent();
	WindowControl.Show();
}





void UI::Manager::MouseMove(MoveArgs args)
{
	(void)args;
}
void UI::Manager::MouseClick(ClickArgs args)
{
	if (Hovering != nullptr)
	{
		Hovering -> RelayClick(args);
	}
	Selected = Hovering;
}
void UI::Manager::MouseScroll(ScrollArgs args)
{
	// scroll hovering
	// if hovering does not have a scroll
	// scroll selected
	if (Selected != nullptr)
	{
		Selected -> RelayScroll(args);
	}
}
void UI::Manager::MouseDrag(DragArgs args)
{
	if (Selected != nullptr)
	{
		Selected -> RelayCursorDrag(args);
	}
}
void UI::Manager::KeyBoardKey(KeyArgs args)
{
	if (Selected != nullptr)
	{
		Selected -> RelayKey(args);
	}
}
void UI::Manager::KeyBoardText(TextArgs args)
{
	if (Selected != nullptr)
	{
		Selected -> RelayText(args);
	}
}



// do this in MouseMove
void UI::Manager::UpdateMouse(DisplayPosition mouse_pos)
{
	CursorPosition = mouse_pos.Buffer.Corner;
	UI::Control::Base * control = WindowControl.CheckHover(mouse_pos.Buffer.Corner);

	if (control != Hovering)
	{
		// this is done in this order so that when the Hover Leave function is called
		// the Manager Hovering is no longer that control
		// Control should not access Manager Hovering
		// change/store hovering state internally ?
		// store hovering this and hovering child ?
		// and hovering parent ?
		// or just dont update color until later ?
		UI::Control::Base * temp = Hovering;
		Hovering = control;
		if (temp != nullptr) { temp -> ChangeHover(UI::Control::Base::HoverArgs::Leave); }
		if (Hovering != nullptr) { Hovering -> ChangeHover(UI::Control::Base::HoverArgs::Enter); }
	}
	if (Hovering != nullptr)
	{
		Hovering -> ChangeHover(UI::Control::Base::HoverArgs::Move);
	}
}
void UI::Manager::Resize(DisplaySize display_size)
{
	TextManager.ShaderLayout.DisplaySize.Put(display_size);
	ControlManager.ShaderLayout.DisplaySize.Put(display_size);
	GraphManager.ShaderLayout.DisplaySize.Put(display_size);

	WindowSize = display_size;
	WindowControl.UpdateWindowSize(WindowSize.Buffer.Full);
}



void UI::Manager::ChangeMedia(const DirectoryInfo & dir, GLFWwindow * glfw_window)
{
	ControlManager.ChangeMedia(dir);

	TextManager.InitMedia(dir);
	TextManager.TextFont = UI::Text::Font::Parse(
		dir.File("Text/Font0.atlas")
	);

	GraphManager.ChangeMedia(dir);

	CursorsCreate(dir, glfw_window);

	WindowControl.ChangeManager(this);
}



void UI::Manager::GraphicsCreate()
{
	ControlManager.GraphicsCreate();
	//ControlManager.CursorsCreate(MediaDirectory);
	TextManager.GraphicsCreate();
	TextManager.InitFont();
	GraphManager.GraphicsCreate();
}
void UI::Manager::GraphicsDelete()
{
	ControlManager.GraphicsDelete();
	TextManager.GraphicsDelete();
	GraphManager.GraphicsDelete();
	CursorsDelete();
}

void UI::Manager::Draw()
{
	WindowControl.Update();

	ControlManager.MakeInstances();
	ControlManager.Draw();

	TextManager.MakeInstances();
	TextManager.Draw();

	GL::Clear(GL::ClearMask::DepthBufferBit);
	GraphManager.MakeInstances();
	GraphManager.Draw();
}
