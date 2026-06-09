#include "Selector.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Miscellaneous/Container/Array.hpp"



SelectorContext::~SelectorContext() { }
SelectorContext::SelectorContext()
	: ContextBase()
	, UIManager()
	, Menu()
{ }

void SelectorContext::Make()
{
	UIManager.WindowControl.ChildInsert(Menu);
}

void SelectorContext::Init()
{
	//window.DefaultColor = ColorF4(0, 0, 0);
	window.DefaultColor = ColorF4(0.5f, 0, 0);

	UIManager.ChangeMedia(MediaDirectory, window.glfw_window);

	UIManager.GraphicsCreate();

	Make();
}
void SelectorContext::Free()
{
	UIManager.GraphicsDelete();
}

void SelectorContext::Resize(DisplaySize display_size)
{
	UIManager.Resize(display_size);
}

void SelectorContext::Frame(FrameTime frame_time)
{
	Menu.TEST_GRAPH.Values.NewValue(frame_time.ActualFramesPerSecond);

	UIManager.UpdateMouse(window.MouseManager.CursorPosition());
	UIManager.Draw();
}

void SelectorContext::MouseMove(MoveArgs args) { UIManager.MouseMove(args); }
void SelectorContext::MouseClick(ClickArgs args) { UIManager.MouseClick(args); }
void SelectorContext::MouseScroll(ScrollArgs args) { UIManager.MouseScroll(args); }
void SelectorContext::MouseDrag(DragArgs args) { UIManager.MouseDrag(args); }
void SelectorContext::KeyBoardKey(KeyArgs args) { UIManager.KeyBoardKey(args); }
void SelectorContext::KeyBoardText(TextArgs args) { UIManager.KeyBoardText(args); }



ContextBase * newSelectorContext()
{
	return new SelectorContext();
}
