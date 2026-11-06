#include "Context.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Generics/Container/Array.hpp"



UserInterfaceContext::UserInterfaceContext()
	: ContextBase()
	, UIManager()
	, Selector()
	, TileGrid()
	, Text()
	, Graph()
	, TestScroll()
	, TestList()
	, DirectoryNavigator()
{
	MediaDirectory = DirectoryInfo("../../media/");
}



void UserInterfaceContext::Make()
{
	UIManager.Window.ChildInsert(Selector);
	UIManager.Window.ChildInsert(TileGrid);
	UIManager.Window.ChildInsert(Text);
	UIManager.Window.ChildInsert(Graph);
	UIManager.Window.ChildInsert(TestScroll);
	UIManager.Window.ChildInsert(TestList);
	UIManager.Window.ChildInsert(DirectoryNavigator);
	UIManager.Window.DepthUpdateRequest();

	TileGrid.Hide();
	Text.Hide();
	Graph.Hide();
	TestScroll.Hide();
	TestList.Hide();
	DirectoryNavigator.Hide();

	Selector.TileGridButton.ClickFunc.Assign(this, &UserInterfaceContext::ToggleTileGrid);
	Selector.TextButton.ClickFunc.Assign(this, &UserInterfaceContext::ToggleText);
	Selector.GraphButton.ClickFunc.Assign(this, &UserInterfaceContext::ToggleGraph);
	Selector.TestScrollButton.ClickFunc.Assign(this, &UserInterfaceContext::ToggleTestScroll);
	Selector.TestListButton.ClickFunc.Assign(this, &UserInterfaceContext::ToggleTestList);
	Selector.DirectoryNavigatorButton.ClickFunc.Assign(this, &UserInterfaceContext::ToggleDirectoryNavigator);

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
static void MenuToggleVisible(UI::Control::Form & form, ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		MenuToggleVisible(form);
	}
}

void UserInterfaceContext::ToggleTileGrid(ClickArgs args)
{
	MenuToggleVisible(TileGrid, args);
}
void UserInterfaceContext::ToggleText(ClickArgs args)
{
	MenuToggleVisible(Text, args);
}
void UserInterfaceContext::ToggleGraph(ClickArgs args)
{
	MenuToggleVisible(Graph, args);
}
void UserInterfaceContext::ToggleTestScroll(ClickArgs args)
{
	MenuToggleVisible(TestScroll, args);
}
void UserInterfaceContext::ToggleTestList(ClickArgs args)
{
	MenuToggleVisible(TestList, args);
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

/* make Function::Relay ?
	Container of Function Pointers
	calls each in order
	maybe return bool to stop relaying ?
*/

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
			TileGrid.Hide();
			Text.Hide();
			Graph.Hide();
			TestScroll.Hide();
			TestList.Hide();
			DirectoryNavigator.Hide();
		}
	}
	UIManager.KeyBoardKey(args);
}
void UserInterfaceContext::KeyBoardText(TextArgs args)	{ UIManager.KeyBoardText(args); }
