#include "Context1.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Miscellaneous/Container/Array.hpp"



Context1::~Context1() { }
Context1::Context1()
	: ContextBase()
	, UIManager()
	, Menu()
{ }



void Context1::Make()
{
	UIManager.WindowControl.ChildInsert(Menu);
}

void Context1::Init()
{
	UIManager.ChangeMedia(MediaDirectory, window.glfw_window);

	UIManager.GraphicsCreate();

	Make();
}
void Context1::Free()
{
	UIManager.GraphicsDelete();
}



void Context1::Resize(DisplaySize display_size)
{
	UIManager.Resize(display_size);
}
void Context1::Frame(FrameTime frame_time)
{
	(void)frame_time;
	UIManager.UpdateMouse(window.MouseManager.CursorPosition());
	UIManager.Draw();
}



void Context1::MouseMove(MoveArgs args) { UIManager.MouseMove(args); }
void Context1::MouseClick(ClickArgs args) { UIManager.MouseClick(args); }
void Context1::MouseScroll(ScrollArgs args) { UIManager.MouseScroll(args); }
void Context1::MouseDrag(DragArgs args) { UIManager.MouseDrag(args); }
void Context1::KeyBoardKey(KeyArgs args) { UIManager.KeyBoardKey(args); }
void Context1::KeyBoardText(TextArgs args) { UIManager.KeyBoardText(args); }



ContextBase * newContext1()
{
	return new Context1();
}
