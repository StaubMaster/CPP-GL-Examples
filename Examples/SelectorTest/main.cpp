#include <iostream>
#include <sstream>
#include <exception>

#include "OpenGL.hpp"
#include "Debug.hpp"

#include "DirectoryInfo.hpp"

#include "ContextBase.hpp"
#include "Context0.hpp"

int main(int argc, char * argv[])
{
	std::cout << "int main() ...\n";
	int ret = -1;
	Debug::NewFileInDir(DirectoryInfo("./logs/"));
	if (argc > 0)	{ Debug::Log << argv[0] << Debug::Done; }
	else			{ Debug::Log << "NoName" << Debug::Done; }
	if (glfwInit() == 0) { std::cout << "GLFW Init Failed\n"; return -1; }
	{
		try
		{
			{
				UndexLoop2D loop(Undex2D(0, 0), Undex2D(1, 1));
				(void)loop;
			}
			Window window;
			Context0 context(window);
			window.CallBack_Init.Assign<ContextBase>(&context, &ContextBase::Init);
			window.CallBack_Free.Assign<ContextBase>(&context, &ContextBase::Free);
			window.CallBack_Resize.Assign<ContextBase>(&context, &ContextBase::Resize);
			window.CallBack_Frame.Assign<ContextBase>(&context, &ContextBase::Frame);
			window.MouseManager.Callback_ScrollEvent.Assign<ContextBase>(&context, &ContextBase::MouseScroll);
			window.MouseManager.Callback_ClickEvent.Assign<ContextBase>(&context, &ContextBase::MouseClick);
			window.MouseManager.Callback_DragEvent.Assign<ContextBase>(&context, &ContextBase::MouseDrag);
			window.KeyBoardManager.CallBack_KeyEvent.Assign<ContextBase>(&context, &ContextBase::KeyBoardKey);
			window.Create();
			Debug::Log << "<<<< Run Window" << Debug::Done;
			window.Run();
			Debug::Log << ">>>> Run Window" << Debug::Done;
			window.Delete();
			std::cout << "MainContext done\n";
		}
		catch (std::exception & ex)
		{ Debug::Log << "Error: " << ex.what() << Debug::Done; }
		catch (...)
		{ Debug::Log << "Error: " << "Unknown" << Debug::Done; }
	}
	glfwTerminate();
	Debug::Log << "main() return " << ret << Debug::Done;
	return ret;
}

