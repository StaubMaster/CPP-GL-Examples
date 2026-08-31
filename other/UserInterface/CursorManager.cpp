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
