
#include "OpenGL.hpp"

#include "Window.hpp"
#include "Context.hpp"

#include <iostream>
#include <exception>

#include "Debug.hpp"

int main()
{
	std::cout << "int main()\n";
	int ret = -1;
	{
		DirectoryInfo log_dir("./logs/");
		if (!log_dir.Exists())
		{
			log_dir.Create();
		}
		Debug::NewFileInDir(log_dir);
	}
	if (glfwInit() == 0)
	{
		std::cerr << "GLFW Init Failed\n";
		ret = -1;
	}
	else
	{
		try
		{
			Window window;
			window.Create();
			{
				Context context(window);
				window.RunLoop();
			}
			window.Delete();
			ret = 0;
		}
		catch (std::exception & ex)
		{
			std::cerr << "Error: " << ex.what() << '\n';
			ret = -1;
		}
		catch (...)
		{
			std::cerr << "Error: " << "Unknown" << '\n';
			ret = -1;
		}
		glfwTerminate();
	}
	std::cout << "main() return " << ret << '\n';
	return 0;
}
