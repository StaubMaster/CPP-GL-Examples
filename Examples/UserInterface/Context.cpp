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
	, Menu3()
	, TestScroll()
{
	MediaDirectory = DirectoryInfo("../../media/");
}



void UserInterfaceContext::Make()
{
	UIManager.WindowControl.ChildInsert(Menu0);
	UIManager.WindowControl.ChildInsert(Menu1);
	UIManager.WindowControl.ChildInsert(Menu2);
	UIManager.WindowControl.ChildInsert(Menu3);
	UIManager.WindowControl.ChildInsert(TestScroll);
	Menu1.Hide();
	Menu2.Hide();
	Menu3.Hide();
	Menu3.Hide();
	TestScroll.Hide();
	Menu0.Menu1Button.ClickFunc.Assign(this, &UserInterfaceContext::Menu1Toggle);
	Menu0.Menu2Button.ClickFunc.Assign(this, &UserInterfaceContext::Menu2Toggle);
	Menu0.Menu3Button.ClickFunc.Assign(this, &UserInterfaceContext::Menu3Toggle);
	Menu0.TestScrollButton.ClickFunc.Assign(this, &UserInterfaceContext::TestScrollToggle);
}

void UserInterfaceContext::Menu1Toggle(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		Menu0.Hide();
		Menu1.Show();
	}
}
void UserInterfaceContext::Menu2Toggle(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		Menu0.Hide();
		Menu2.Show();
	}
}
void UserInterfaceContext::Menu3Toggle(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		Menu0.Hide();
		Menu3.Show();
	}
}
void UserInterfaceContext::TestScrollToggle(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		Menu0.Hide();
		TestScroll.Show();
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



#include <iostream>
#include "ValueType/_Show.hpp"
void UserInterfaceContext::Resize(DisplaySize display_size)
{
	UIManager.Resize(display_size);
}
void UserInterfaceContext::Frame(FrameTime frame_time)
{
	(void)frame_time;
//	std::cout << "Mouse: " << window.MouseManager.CursorPosition().Window.Corner << '\n';
	UIManager.UpdateMouse(window.MouseManager.CursorPosition());
	UIManager.Draw();
}



void UserInterfaceContext::MouseMove(MoveArgs args) { UIManager.MouseMove(args); }
void UserInterfaceContext::MouseClick(ClickArgs args) { UIManager.MouseClick(args); }
void UserInterfaceContext::MouseScroll(ScrollArgs args) { UIManager.MouseScroll(args); }
void UserInterfaceContext::MouseDrag(DragArgs args) { UIManager.MouseDrag(args); }
void UserInterfaceContext::KeyBoardKey(KeyArgs args)
{
	if (args.Key == Keys::Escape)
	{
		if (args.Action == Action::Press)
		{
			Menu0.Show();
			Menu1.Hide();
			Menu2.Hide();
			Menu3.Hide();
			TestScroll.Hide();
		}
	}
	else
	{
		UIManager.KeyBoardKey(args);
	}
}
void UserInterfaceContext::KeyBoardText(TextArgs args) { UIManager.KeyBoardText(args); }
