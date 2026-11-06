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
	, DirectoryNavigator()
{
	MediaDirectory = DirectoryInfo("../../media/");
}



void UserInterfaceContext::Make()
{
	UIManager.Window.ChildInsert(Menu0);
	UIManager.Window.ChildInsert(Menu1);
	UIManager.Window.ChildInsert(Menu2);
	UIManager.Window.ChildInsert(Menu3);
	UIManager.Window.ChildInsert(TestScroll);
	UIManager.Window.ChildInsert(TestList);
	UIManager.Window.ChildInsert(DirectoryNavigator);
	UIManager.Window.DepthUpdateRequest();

	Menu1.Hide();
	Menu2.Hide();
	Menu3.Hide();
	Menu3.Hide();
	TestScroll.Hide();
	TestList.Hide();
	DirectoryNavigator.Hide();

	Menu0.Menu1Button.ClickFunc.Assign(this, &UserInterfaceContext::ToggleMenu1);
	Menu0.Menu2Button.ClickFunc.Assign(this, &UserInterfaceContext::ToggleMenu2);
	Menu0.Menu3Button.ClickFunc.Assign(this, &UserInterfaceContext::ToggleMenu3);
	Menu0.TestScrollButton.ClickFunc.Assign(this, &UserInterfaceContext::ToggleTestScroll);
	Menu0.TestListButton.ClickFunc.Assign(this, &UserInterfaceContext::ToggleTestList);
	Menu0.DirectoryNavigatorButton.ClickFunc.Assign(this, &UserInterfaceContext::ToggleDirectoryNavigator);

	DirectoryNavigator.Change(MediaDirectory);
	//DirectoryNavigator.Change(DirectoryInfo(MediaDirectory.Path.ToAbsolute()));

	UIManager.Window.DepthUpdateRequest();
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
		MenuToggleVisible(TestList);
	}
}
void UserInterfaceContext::ToggleDirectoryNavigator(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		MenuToggleVisible(DirectoryNavigator);
		//DirectoryNavigator.FileList.CalcScroll();
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



#include "Text/ObjectData.hpp"
void UserInterfaceContext::Frame(FrameTime frame_time)
{
	(void)frame_time;

	UIManager.UpdateMouse(window.MouseManager.CursorPosition());
	UIManager.Update();

	UIManager.GraphicsClear();
	/*{
		UI::Text::ObjectData data;
		data.Text = "TEST\ntest";
		data.TextPosition = window.Size.Buffer.Half;
		data.TextAlignmentX = UI::Text::Alignment::Mid;
		data.TextAlignmentY = UI::Text::Alignment::Mid;
		data.CharacterSize = VectorF2(128);
		data.CharacterAlignmentX = UI::Text::Alignment::Mid;
		data.CharacterAlignmentY = UI::Text::Alignment::Mid;
		data.Bound = BoxF2(VectorF2(), window.Size.Buffer.Full);
		data.Color0 = ColorF4(1, 1, 1);
		data.Color1 = ColorF4(0, 0, 0);
		data.Depth = 0.5f;
		UIManager.TextManager.InstancesPut(data);
	}*/
	UIManager.GraphicsMake();
	UIManager.GraphicsDone();

	UIManager.GraphicsDraw();
}
void UserInterfaceContext::Resize(DisplaySize display_size)
{
	UIManager.Resize(display_size);
}
void UserInterfaceContext::MouseMove(MoveArgs args)		{ UIManager.MouseMove(args); }
void UserInterfaceContext::MouseClick(ClickArgs args)	{ UIManager.MouseClick(args); }
void UserInterfaceContext::MouseScroll(ScrollArgs args)	{ UIManager.MouseScroll(args); }
void UserInterfaceContext::MouseDrag(DragArgs args)		{ UIManager.MouseDrag(args); }
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
			TestList.Hide();
			DirectoryNavigator.Hide();
		}
	}
	else
	{
		UIManager.KeyBoardKey(args);
	}
}
void UserInterfaceContext::KeyBoardText(TextArgs args)	{ UIManager.KeyBoardText(args); }
