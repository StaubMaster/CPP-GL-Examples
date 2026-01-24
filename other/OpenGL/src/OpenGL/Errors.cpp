#include "OpenGL/Errors.hpp"
#include "OpenGL/openGL.hpp"



const char * GLErrorString()
{
	switch (glGetError())
	{
		case GL_NO_ERROR:						return "NO_ERROR";
		case GL_INVALID_ENUM:					return "INVALID_ENUM";
		case GL_INVALID_VALUE:					return "INVALID_VALUE";
		case GL_INVALID_OPERATION:				return "INVALID_OPERATION";
		case GL_INVALID_FRAMEBUFFER_OPERATION:	return "INVALID_FRAMEBUFFER_OPERATION";
		case GL_OUT_OF_MEMORY:					return "OUT_OF_MEMORY";
		case GL_STACK_UNDERFLOW:				return "STACK_UNDERFLOW";
		case GL_STACK_OVERFLOW:					return "STACK_OVERFLOW";
	}
	return NULL;
}
