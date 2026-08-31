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
	//, TestList()
	, DirectoryNavigator()
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
	//UIManager.WindowControl.ChildInsert(TestList);
	UIManager.WindowControl.ChildInsert(DirectoryNavigator);
	UIManager.WindowControl.UpdateDepth();

	Menu1.Hide();
	Menu2.Hide();
	Menu3.Hide();
	Menu3.Hide();
	TestScroll.Hide();
	//TestList.Hide();
	DirectoryNavigator.Hide();

	Menu0.Menu1Button.ClickFunc.Assign(this, &UserInterfaceContext::ToggleMenu1);
	Menu0.Menu2Button.ClickFunc.Assign(this, &UserInterfaceContext::ToggleMenu2);
	Menu0.Menu3Button.ClickFunc.Assign(this, &UserInterfaceContext::ToggleMenu3);
	Menu0.TestScrollButton.ClickFunc.Assign(this, &UserInterfaceContext::ToggleTestScroll);
	//Menu0.TestListButton.ClickFunc.Assign(this, &UserInterfaceContext::ToggleTestList);
	Menu0.DirectoryNavigatorButton.ClickFunc.Assign(this, &UserInterfaceContext::ToggleDirectoryNavigator);

	DirectoryNavigator.Change(MediaDirectory);

	UIManager.WindowControl.UpdateDepth();
}

static void MenuToggleVisible(UI::Control::Form & form)
{
	if (form.IsVisible())
	{
		form.Hide();
	}
	else
	{
		form.Show();
	}
}

void UserInterfaceContext::ToggleMenu1(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		MenuToggleVisible(Menu1);
	}
}
void UserInterfaceContext::ToggleMenu2(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		MenuToggleVisible(Menu2);
	}
}
void UserInterfaceContext::ToggleMenu3(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		MenuToggleVisible(Menu3);
	}
}
void UserInterfaceContext::ToggleTestScroll(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		MenuToggleVisible(TestScroll);
	}
}
void UserInterfaceContext::ToggleTestList(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		//MenuToggleVisible(TestList);
	}
}
void UserInterfaceContext::ToggleDirectoryNavigator(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		MenuToggleVisible(DirectoryNavigator);
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
	UIManager.Update();
	/*UIManager.Update()
		update Depth automatically
			instead of using range ]0;1[
			just use 0 to n
			disable depth clamp
			keep depth test
	*/
	UIManager.GraphicsMake();
	UIManager.GraphicsDraw();
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
			Menu1.Hide();
			Menu2.Hide();
			Menu3.Hide();
			TestScroll.Hide();
			//TestList.Hide();
			DirectoryNavigator.Hide();
		}
	}
	else
	{
		UIManager.KeyBoardKey(args);
	}
}
void UserInterfaceContext::KeyBoardText(TextArgs args) { UIManager.KeyBoardText(args); }
