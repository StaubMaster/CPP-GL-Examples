#include "CursorManager.hpp"

#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"
#include "Image.hpp"



UI::CursorManager::~CursorManager()
{ }
UI::CursorManager::CursorManager()
	: Position()
	, glfw_window(nullptr)
	, glfw_cursorArrowC(nullptr)
	, glfw_cursorArrowH(nullptr)
	, glfw_cursorArrowV(nullptr)
	, glfw_cursorArrowD0(nullptr)
	, glfw_cursorArrowD1(nullptr)
	, glfw_cursorBoxEdge{ nullptr, nullptr, nullptr, nullptr }
	, glfw_cursorBoxCorn{ nullptr, nullptr, nullptr, nullptr }
{ }



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

void UI::CursorManager::Create(const DirectoryInfo & dir, GLFWwindow * glfw_window)
{
	this -> glfw_window = glfw_window;

	DirectoryInfo cursor_dir = dir.Directory("Images/Cursors/");

	glfw_cursorArrowC  = ImageToCursor(cursor_dir.File("ArrowCross.png").LoadImage());
	glfw_cursorArrowH  = ImageToCursor(cursor_dir.File("ArrowHori.png").LoadImage());
	glfw_cursorArrowV  = ImageToCursor(cursor_dir.File("ArrowVert.png").LoadImage());
	glfw_cursorArrowD0 = ImageToCursor(cursor_dir.File("ArrowDiag0.png").LoadImage());
	glfw_cursorArrowD1 = ImageToCursor(cursor_dir.File("ArrowDiag1.png").LoadImage());

	glfw_cursorBoxEdge[0] = ImageToCursor(cursor_dir.File("BoxHoriMin.png").LoadImage());
	glfw_cursorBoxEdge[1] = ImageToCursor(cursor_dir.File("BoxVertMin.png").LoadImage());
	glfw_cursorBoxEdge[2] = ImageToCursor(cursor_dir.File("BoxHoriMax.png").LoadImage());
	glfw_cursorBoxEdge[3] = ImageToCursor(cursor_dir.File("BoxVertMax.png").LoadImage());

	glfw_cursorBoxCorn[0] = ImageToCursor(cursor_dir.File("BoxMinMin.png").LoadImage());
	glfw_cursorBoxCorn[1] = ImageToCursor(cursor_dir.File("BoxMaxMin.png").LoadImage());
	glfw_cursorBoxCorn[2] = ImageToCursor(cursor_dir.File("BoxMinMax.png").LoadImage());
	glfw_cursorBoxCorn[3] = ImageToCursor(cursor_dir.File("BoxMaxMax.png").LoadImage());
}
void UI::CursorManager::Delete()
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

void UI::CursorManager::UseDefault() { if (glfw_window != nullptr) { glfwSetCursor(glfw_window, nullptr); } }
void UI::CursorManager::UseArrowC()  { if (glfw_window != nullptr) { glfwSetCursor(glfw_window, glfw_cursorArrowC); } }
void UI::CursorManager::UseArrowH()  { if (glfw_window != nullptr) { glfwSetCursor(glfw_window, glfw_cursorArrowH); } }
void UI::CursorManager::UseArrowV()  { if (glfw_window != nullptr) { glfwSetCursor(glfw_window, glfw_cursorArrowV); } }
void UI::CursorManager::UseArrowD0() { if (glfw_window != nullptr) { glfwSetCursor(glfw_window, glfw_cursorArrowD0); } }
void UI::CursorManager::UseArrowD1() { if (glfw_window != nullptr) { glfwSetCursor(glfw_window, glfw_cursorArrowD1); } }
void UI::CursorManager::UseBoxEdge(unsigned char i) { if (glfw_window != nullptr) { glfwSetCursor(glfw_window, glfw_cursorBoxEdge[i]); } }
void UI::CursorManager::UseBoxCorn(unsigned char i) { if (glfw_window != nullptr) { glfwSetCursor(glfw_window, glfw_cursorBoxCorn[i]); } }
