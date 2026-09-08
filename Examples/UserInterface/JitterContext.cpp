#include "Context.hpp"
#include "Window.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Generics/Container/Array.hpp"



UserInterfaceContext::~UserInterfaceContext() { }
UserInterfaceContext::UserInterfaceContext()
	: ContextBase()
	, UIManager()
	, JitterTest()
{
	MediaDirectory = DirectoryInfo("../../media/");
}



void UserInterfaceContext::Make()
{
	UIManager.Window.ChildInsert(JitterTest);
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
static int ResizeLimit = 16;
void UserInterfaceContext::Resize(DisplaySize display_size)
{
	(void)display_size;
	static bool only_once = true;
	std::cout << "Context::Resize ....\n";
	if (only_once)
	{
		UIManager.Resize(display_size);
		only_once = false;
	}
	/*{
		std::cout << "Forms[\n";
		for (unsigned int i = 0; i < UIManager.Window.Children.Count(); i++)
		{
			const UI::Control::Base & control = *UIManager.Window.Children[i];
			std::cout << control.BoxDisplay << '\n';
		}
		std::cout << "]Forms\n";
	}*/
	std::cout << "Context::Resize done\n";
	ResizeLimit--;
}
void UserInterfaceContext::Frame(FrameTime frame_time)
{
	std::cout << "Context::Frame ....\n";
	(void)frame_time;
	UIManager.UpdateMouse(window.MouseManager.CursorPosition());
	UIManager.Update();
	/*{
		std::cout << "Forms[\n";
		for (unsigned int i = 0; i < UIManager.Window.Children.Count(); i++)
		{
			const UI::Control::Base & control = *UIManager.Window.Children[i];
			std::cout << control.BoxDisplay << '\n';
		}
		std::cout << "]Forms\n";
	}*/
	UIManager.GraphicsMake();
	UIManager.GraphicsDraw();
	{
		std::cout << "Data[\n";
		for (unsigned int i = 0; i < UIManager.ControlManager.Instances.Count(); i++)
		{
			const UI::Control::Inst::BufferData & data = UIManager.ControlManager.Instances[i];
			std::cout << data.Box << '\n';
		}
		std::cout << "]Data\n";
	}
	std::cout << "Context::Frame done\n";
	/*if (ResizeLimit <= 0)
	{
		std::cout << "Resize Limit Exit\n";
		window.ExitLoop();
	}*/
}



void UserInterfaceContext::MouseMove(MoveArgs args) { UIManager.MouseMove(args); }
void UserInterfaceContext::MouseClick(ClickArgs args) { UIManager.MouseClick(args); }
void UserInterfaceContext::MouseScroll(ScrollArgs args) { UIManager.MouseScroll(args); }
void UserInterfaceContext::MouseDrag(DragArgs args) { UIManager.MouseDrag(args); }
void UserInterfaceContext::KeyBoardKey(KeyArgs args) { UIManager.KeyBoardKey(args); }
void UserInterfaceContext::KeyBoardText(TextArgs args) { UIManager.KeyBoardText(args); }
