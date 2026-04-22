#include <iostream>
#include <sstream>
#include <exception>

#include "OpenGL.hpp"
#include "Debug.hpp"

#include "DirectoryInfo.hpp"

#include "Window.hpp"
#include "ContextBase.hpp"

#include "ValueType/UndexLoop2D.hpp"

int main(int argc, char * argv[])
{
	std::cout << "int main() ...\n";
	int ret = -1;
	{ UndexLoop2D loop(Undex2D(0, 0), Undex2D(1, 1)); (void)loop; } // compiler complaining
	Debug::NewFileInDir(DirectoryInfo("./logs/"));
	if (argc > 0)	{ Debug::Log << argv[0] << Debug::Done; }
	else			{ Debug::Log << "NoName" << Debug::Done; }
	if (glfwInit() == 0) { std::cout << "GLFW Init Failed\n"; return -1; }
	{
		try
		{
			Window window;
			window.Create();
			ContextBase::WindowPointer = &window;
			ContextBase::ChangeToContext0();
			while (ContextBase::ContextToUse != nullptr)
			{
				ContextBase * context = ContextBase::ContextToUse;
				ContextBase::ContextToUse = nullptr;
				context -> Run();
				delete context;
			}
			window.Delete();
			ContextBase::WindowPointer = nullptr;
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
