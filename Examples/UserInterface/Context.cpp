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
	, TestList()
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
	UIManager.WindowControl.ChildInsert(TestList);
	Menu1.Hide();
	Menu2.Hide();
	Menu3.Hide();
	Menu3.Hide();
	TestScroll.Hide();
	TestList.Hide();
	Menu0.Menu1Button.ClickFunc.Assign(this, &UserInterfaceContext::ToggleMenu1);
	Menu0.Menu2Button.ClickFunc.Assign(this, &UserInterfaceContext::ToggleMenu2);
	Menu0.Menu3Button.ClickFunc.Assign(this, &UserInterfaceContext::ToggleMenu3);
	Menu0.TestScrollButton.ClickFunc.Assign(this, &UserInterfaceContext::ToggleTestScroll);
	Menu0.TestListButton.ClickFunc.Assign(this, &UserInterfaceContext::ToggleTestList);
}

void UserInterfaceContext::ToggleMenu1(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		Menu0.Hide();
		Menu1.Show();
	}
}
void UserInterfaceContext::ToggleMenu2(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		Menu0.Hide();
		Menu2.Show();
	}
}
void UserInterfaceContext::ToggleMenu3(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		Menu0.Hide();
		Menu3.Show();
	}
}
void UserInterfaceContext::ToggleTestScroll(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		Menu0.Hide();
		TestScroll.Show();
	}
}
void UserInterfaceContext::ToggleTestList(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		Menu0.Hide();
		TestList.Show();
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
			TestList.Hide();
		}
	}
	else
	{
		UIManager.KeyBoardKey(args);
	}
}
void UserInterfaceContext::KeyBoardText(TextArgs args) { UIManager.KeyBoardText(args); }
