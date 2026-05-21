#include <iostream>
#include <sstream>
#include <exception>

#include "OpenGL.hpp"
#include "Debug.hpp"

#include "DirectoryInfo.hpp"

#include "Window.hpp"
#include "ContextBase.hpp"

#include "ValueType/LoopU2.hpp"

int main(int argc, char * argv[])
{
	std::cout << "int main() ...\n";
	int ret = -1;
	{ LoopU2 loop(VectorU2(0, 0), VectorU2(1, 1)); (void)loop; } // compiler complaining
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
			//ContextBase::ChangeToTestTextAlignment();
			while (ContextBase::NewContext.Function != nullptr)
			{
				ContextBase * context = ContextBase::NewContext.Invoke();
				ContextBase::NewContext.Assign(nullptr);
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
