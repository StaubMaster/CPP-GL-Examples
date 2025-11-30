
#include <iostream>
#include "OpenGL/openGL.h"

#include "Debug.hpp"

#include "Window.hpp"

#include <signal.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>



Window * win;



void Init()
{
	std::cout << "Init ...\n";
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	std::cout << "Init done\n";
}
void Free()
{
	std::cout << "Free ...\n";
	std::cout << "Free done\n";
}

void Frame(double timeDelta)
{
	(void)timeDelta;
}
void Resize(int w, int h)
{
	(void)w;
	(void)h;
}





void signal_handler(int s)
{
	std::cout << "\nSignal " << s << "\n";
	std::cout << "SIGINT " << SIGINT << "\n";
	std::cout << "done\n";
	glfwSetWindowShouldClose(win -> win, GL_TRUE);
}

int main()
{
	try
	{
		signal(SIGINT, signal_handler);

		if (glfwInit() == 0)
		{
			std::cout << "GLFW Init Failed\n";
			return -1;
		}

		win = new Window(640, 480);
		win -> InitFunc = Init;
		win -> FreeFunc = Free;
		win -> FrameFunc = Frame;
		win -> ResizeFunc = Resize;

		std::cout << "<<<< Run Window" << '\n';
		win -> Run();
		std::cout << ">>>> Run Window" << '\n';

		delete win;
		glfwTerminate();
	}
	catch (std::exception & ex)
	{
		std::cerr << "Error: " << ex.what() << '\n';
	}
	catch (...)
	{
		std::cerr << "Error: " << "Unknown" << '\n';
	}

	std::cout << "_CrtSetReportMode " << _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG) << '\n';
	std::cout << "_CrtDumpMemoryLeaks " << _CrtDumpMemoryLeaks() << '\n';

	std::cout << "main() return\n";
	return 0;
}
