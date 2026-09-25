#include <iostream>
//#include "OpenGL.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

int main()
{
	std::cout << "test\n";
	if (!glfwInit())
	{
		std::cerr << "GLFW Init Failed\n";
		return 1;
	}

	GLFWwindow * win = glfwCreateWindow(480, 360, "Window", NULL, NULL);
	if (win == NULL)
	{
		std::cerr << "Window Failed\n";
		return 1;
	}

	glfwMakeContextCurrent(win);

	//	this is what causes the PIE object stuff
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "glad load GL-Loader Failed\n";
		return 1;
	}

	while (!glfwWindowShouldClose(win))
	{
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
