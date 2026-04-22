#include "main.hpp"

#include <iostream>
#include <sstream>
#include <exception>

#include "OpenGL.hpp"
#include "Debug.hpp"

#include "DirectoryInfo.hpp"

#include "Context0.hpp"
#include "Context1.hpp"



Window * window_ptr = nullptr;
ContextBase * ContextToUse = nullptr;

void	QuitContext()
{
	ContextToUse = nullptr;
	if (window_ptr != nullptr)
	{
		window_ptr -> ExitLoop();
	}
}
void	ChangeContext(ContextBase * context)
{
	ContextToUse = context;
	if (window_ptr != nullptr)
	{
		window_ptr -> ExitLoop();
	}
}
void	ChangeToContext0()
{
	std::cout << "ChangeToContext0\n";
	ChangeContext(new Context0(*window_ptr));
}
void	ChangeToContext1()
{
	std::cout << "ChangeToContext1\n";
	ChangeContext(new Context1(*window_ptr));
}



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
			{ UndexLoop2D loop(Undex2D(0, 0), Undex2D(1, 1)); (void)loop; }
			Window window;
			window.Create();
			window_ptr = &window;
			ContextToUse = new Context0(window);
			while (ContextToUse != nullptr)
			{
				ContextBase * context = ContextToUse;
				ContextToUse = nullptr;

				window.CallBack_Init.Assign<ContextBase>(context, &ContextBase::Init);
				window.CallBack_Free.Assign<ContextBase>(context, &ContextBase::Free);
				window.CallBack_Resize.Assign<ContextBase>(context, &ContextBase::Resize);
				window.CallBack_Frame.Assign<ContextBase>(context, &ContextBase::Frame);
				window.MouseManager.Callback_ScrollEvent.Assign<ContextBase>(context, &ContextBase::MouseScroll);
				window.MouseManager.Callback_ClickEvent.Assign<ContextBase>(context, &ContextBase::MouseClick);
				window.MouseManager.Callback_DragEvent.Assign<ContextBase>(context, &ContextBase::MouseDrag);
				window.KeyBoardManager.CallBack_KeyEvent.Assign<ContextBase>(context, &ContextBase::KeyBoardKey);

				Debug::Log << "<<<< Run Window" << Debug::Done;
				window.RunLoop();
				Debug::Log << ">>>> Run Window" << Debug::Done;

				delete context;
			}
			window.Delete();
			window_ptr = nullptr;
			ret = 0;
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

