#include "Context.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Generics/Container/Array.hpp"



UserInterfaceContext::~UserInterfaceContext() { }
UserInterfaceContext::UserInterfaceContext()
	: ContextBase()
	, UIManager()
	, Menu0()
	, Menu1()
	, Menu2()
{
	MediaDirectory = DirectoryInfo("../../media/");
}



void UserInterfaceContext::Make()
{
	UIManager.WindowControl.ChildInsert(Menu0);
	UIManager.WindowControl.ChildInsert(Menu1);
	UIManager.WindowControl.ChildInsert(Menu2);
	UIManager.WindowControl.ChildInsert(Menu3);
	Menu1.Hide();
	Menu2.Hide();
	Menu3.Hide();
	Menu0.Menu1Button.ClickFunc.Assign(this, &UserInterfaceContext::Menu1Toggle);
	Menu0.Menu2Button.ClickFunc.Assign(this, &UserInterfaceContext::Menu2Toggle);
	Menu0.Menu3Button.ClickFunc.Assign(this, &UserInterfaceContext::Menu3Toggle);
}

void UserInterfaceContext::Menu1Toggle(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		if (Menu1.IsVisible())
		{ Menu1.Hide(); }
		else
		{ Menu1.Show(); }
	}
}
void UserInterfaceContext::Menu2Toggle(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		if (Menu2.IsVisible())
		{ Menu2.Hide(); }
		else
		{ Menu2.Show(); }
	}
}
void UserInterfaceContext::Menu3Toggle(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		if (Menu3.IsVisible())
		{ Menu3.Hide(); }
		else
		{ Menu3.Show(); }
	}
}



void UserInterfaceContext::Init()
{
	UIManager.ChangeMedia(MediaDirectory, window.glfw_window);

	UIManager.GraphicsCreate();

	UIManager.GraphicsInit();

	Make();
}
void UserInterfaceContext::Free()
{
	UIManager.GraphicsDelete();
}



void UserInterfaceContext::Resize(DisplaySize display_size)
{
	UIManager.Resize(display_size);
}
void UserInterfaceContext::Frame(FrameTime frame_time)
{
	(void)frame_time;
	UIManager.UpdateMouse(window.MouseManager.CursorPosition());
	UIManager.Draw();
}



void UserInterfaceContext::MouseMove(MoveArgs args) { UIManager.MouseMove(args); }
void UserInterfaceContext::MouseClick(ClickArgs args) { UIManager.MouseClick(args); }
void UserInterfaceContext::MouseScroll(ScrollArgs args) { UIManager.MouseScroll(args); }
void UserInterfaceContext::MouseDrag(DragArgs args) { UIManager.MouseDrag(args); }
void UserInterfaceContext::KeyBoardKey(KeyArgs args) { UIManager.KeyBoardKey(args); }
void UserInterfaceContext::KeyBoardText(TextArgs args) { UIManager.KeyBoardText(args); }
