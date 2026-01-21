#include "openGL.hpp"
#include "openGL.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>



int OpenGL::getInt(unsigned int name)
{
	int data;
	glGetIntegerv(name, &data);
	return data;
}
int OpenGL::getInt(unsigned int name, unsigned int index)
{
	int data;
	glGetIntegeri_v(name, index, &data);
	return data;
}



void OpenGL::ShowContextInfo()
{
	std::cout << "OpenGL Context Info\n";

	{
		//int versionMajor;
		//int versionMinor;
		//glgetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		//glgetIntegerv(GL_MINOR_VERSION, &versionMinor);
		//std::cout << "Version: " << versionMajor << "." << versionMinor << "\n";
		std::cout << "Version: " << getInt(GL_MAJOR_VERSION) << "." << getInt(GL_MINOR_VERSION) << "\n";
	}

	{
		int context = getInt(GL_CONTEXT_FLAGS);
		std::cout << "Context: 0x" << std::hex << context << "\n";
		std::cout << "  GL_CONTEXT_COMPATIBILITY_PROFILE_BIT " << ((context & GL_CONTEXT_COMPATIBILITY_PROFILE_BIT) != 0) << "\n";
		std::cout << "  GL_CONTEXT_CORE_PROFILE_BIT " << ((context & GL_CONTEXT_CORE_PROFILE_BIT) != 0) << "\n";
		std::cout << "  GL_CONTEXT_FLAG_DEBUG_BIT " << ((context & GL_CONTEXT_FLAG_DEBUG_BIT) != 0) << "\n";
		std::cout << "  GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT " << ((context & GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT) != 0) << "\n";
		std::cout << "  GL_CONTEXT_FLAG_NO_ERROR_BIT " << ((context & GL_CONTEXT_FLAG_NO_ERROR_BIT) != 0) << "\n";
		std::cout << "  GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT " << ((context & GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT) != 0) << "\n";
		std::cout << std::dec;
	}
}
void OpenGL::ShowCurrentInfo()
{
	std::cout << "OpenGL Current Info\n";
	std::cout << "Shader Program: " << getInt(GL_CURRENT_PROGRAM) << "\n";
	std::cout << "Array Buffer: " << getInt(GL_VERTEX_ARRAY_BINDING) << "\n";
	std::cout << "Texture Buffer: " << getInt(GL_TEXTURE_BINDING_BUFFER) << "\n";
	{
		std::cout << "Texture 1D: " << getInt(GL_TEXTURE_BINDING_1D) << "\n";
		std::cout << "Texture 2D: " << getInt(GL_TEXTURE_BINDING_2D) << "\n";
		std::cout << "Texture 3D: " << getInt(GL_TEXTURE_BINDING_3D) << "\n";

		std::cout << "Texture 1D Array: " << getInt(GL_TEXTURE_BINDING_1D_ARRAY) << "\n";
		std::cout << "Texture 2D Array: " << getInt(GL_TEXTURE_BINDING_2D_ARRAY) << "\n";
		
		std::cout << "Texture 2D Multisample: " << getInt(GL_TEXTURE_BINDING_2D_MULTISAMPLE) << "\n";
		std::cout << "Texture 2D Multisample Array: " << getInt(GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY) << "\n";

		std::cout << "Texture Cube Map: " << getInt(GL_TEXTURE_BINDING_CUBE_MAP) << "\n";
		std::cout << "Texture Cube Map Array: " << getInt(GL_TEXTURE_BINDING_CUBE_MAP_ARRAY) << "\n";
		std::cout << "Texture Rectangle: " << getInt(GL_TEXTURE_BINDING_RECTANGLE) << "\n";
	}
}



/*std::string StringToLength(std::string str, unsigned int len; char paddingChar = ' ')
{
	if (str.length() == len)
	{
		return str;
	}
	else if (str.length() < len)
	{
		char chr[len];
		for (unsigned int i = 0; i < str.length(); i++)
		{
			chr[i] = str[i];
		}
		for (unsigned int i = str.length(); i < len; i++)
		{
			chr[i] = paddingChar;
		}
		return std::string(chr, len);
	}
	else if (str.length() > len)
	{
		char chr[len];
		for (unsigned int i = 0; i < len; i++)
		{
			chr[i] = str[i];
		}
		return std::string(chr, len);
	}
}*/
static void ShowTablePaddingRow(unsigned int nameSize, unsigned int dataSize, unsigned int colCount)
{
	std::cout << std::string(nameSize, '-');
	for (unsigned int x = 0; x < colCount; x++)
	{
		std::cout << "-#-";
		std::cout << std::string(dataSize, '-');
	}
	std::cout << "-#\n";
}
static void ShowTable(
	unsigned int colCount, std::string colNames[],
	unsigned int rowCount, std::string rowNames[],
	unsigned int nameSize, unsigned int dataSize,
	int data[])
{
	ShowTablePaddingRow(nameSize, dataSize, colCount);

	{
		std::cout << std::string(nameSize, ' ');
		std::cout << std::right;
		for (unsigned int x = 0; x < colCount; x++)
		{
			std::cout << " | ";
			std::cout << std::setw(dataSize);
			std::cout << colNames[x];
		}
		std::cout << " |\n";
	}

	ShowTablePaddingRow(nameSize, dataSize, colCount);

	for (unsigned int y = 0; y < rowCount; y++)
	{
		std::cout << std::left;
		std::cout << std::setw(nameSize);
		std::cout << rowNames[y];
		std::cout << std::right;
		for (unsigned int x = 0; x < colCount; x++)
		{
			std::cout << " | ";
			std::cout << std::setw(dataSize);
			int & d = data[x * rowCount + y];
			if (d == -1)
			{ std::cout << " "; }
			else
			{ std::cout << d; }
		}
		std::cout << " |\n";
	}

	ShowTablePaddingRow(nameSize, dataSize, colCount);
}
/*
	make a table class/struct
	have it automatically figure out string padding
	this is way too much for what this is supposed to be ?
*/



void OpenGL::ShowGeneralLimits()
{
	{
		//	General
		//GL_MAX_VIEWPORT_DIMS
		//GL_MAX_VIEWPORTS
		
		//GL_MAX_CULL_DISTANCES
		//GL_MAX_CLIP_DISTANCES
		//GL_MAX_CLIP_PLANES
		//GL_MAX_DEPTH
	}
}
void OpenGL::ShowUniformLimits()
{
	std::cout << "OpenGL Limits Uniforms\n";
	ShowTable(
		1, (std::string[]) {
			"",
		},
		3, (std::string[]) {
			"Locations",
			"Block Size",
			"Buffer Bindings",
		},
		15, 7,
		(int []) {
			getInt(GL_MAX_UNIFORM_LOCATIONS),
			getInt(GL_MAX_UNIFORM_BLOCK_SIZE),
			getInt(GL_MAX_UNIFORM_BUFFER_BINDINGS),
		}
	);
	std::cout << "\n";
	ShowTable(
		3, (std::string[]) {
			"Vert",
			"Geom",
			"Frag",
		},
		4, (std::string[]) {
			"Blocks",
			"Vectors",
			"Components",
			"Combined Components",
		},
		20, 8,
		(int []) {
			getInt(GL_MAX_VERTEX_UNIFORM_BLOCKS),
			getInt(GL_MAX_VERTEX_UNIFORM_COMPONENTS),
			getInt(GL_MAX_VERTEX_UNIFORM_VECTORS),
			getInt(GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS),

			getInt(GL_MAX_GEOMETRY_UNIFORM_BLOCKS),
			-1,
			getInt(GL_MAX_GEOMETRY_UNIFORM_COMPONENTS),
			getInt(GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS),
			
			getInt(GL_MAX_FRAGMENT_UNIFORM_BLOCKS),
			getInt(GL_MAX_FRAGMENT_UNIFORM_VECTORS),
			getInt(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS),
			getInt(GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS),
		}
	);
}
void OpenGL::ShowTextureLimits()
{
	ShowTable(
		4, (std::string[]) {
			"Vert",
			"Geom",
			"Frag",
			"All",
		},
		3, (std::string[]) {
			"Texture Image Units",
			"Image Uniforms",
			"Combined Image Uniforms",
		},
		23, 4,
		(int []) {
			getInt(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS),
			getInt(GL_MAX_VERTEX_IMAGE_UNIFORMS),
			-1,

			getInt(GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS),
			getInt(GL_MAX_GEOMETRY_IMAGE_UNIFORMS),
			-1,

			-1,
			getInt(GL_MAX_FRAGMENT_IMAGE_UNIFORMS),
			-1,

			-1,
			-1,
			getInt(GL_MAX_COMBINED_IMAGE_UNIFORMS),
		}
	);

	{
		//	Textures
		//GL_MAX_ARRAY_TEXTURE_LAYERS
		//GL_MAX_3D_TEXTURE_SIZE
		//GL_MAX_TEXTURE_BUFFER_SIZE
		//GL_MAX_TEXTURE_COORDS
		//GL_MAX_TEXTURE_IMAGE_UNITS
		//GL_MAX_TEXTURE_SIZE
		//GL_MAX_TEXTURE_STACK_DEPTH
		//GL_MAX_TEXTURE_UNITS
	}
}
void OpenGL::ShowVertexLimits()
{
	std::cout << "OpenGL Limits Shader Vertex\n";
	ShowTable(
		1, (std::string[]) {
			"",
		},
		4, (std::string[]) {
			"Attribs",
			"Attrib Bindings",
			"Attrib Stride",
			"Attrib Relative Offset",
		},
		22, 4,
		(int []) {
			getInt(GL_MAX_VERTEX_ATTRIBS),
			getInt(GL_MAX_VERTEX_ATTRIB_BINDINGS),
			getInt(GL_MAX_VERTEX_ATTRIB_STRIDE),
			getInt(GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET),
		}
	);
}
void OpenGL::ShowLimits()
{
	std::cout << "\n";
	ShowGeneralLimits();
	std::cout << "\n";
	ShowUniformLimits();
	std::cout << "\n";

	ShowTable(
		3, (std::string[]) {
			"Vert",
			"Geom",
			"Frag",
		},
		3, (std::string[]) {
			"Input Components",
			"Output Components",
			"Total Output Components",
		},
		23, 4,
		(int []) {
			-1,
			getInt(GL_MAX_VERTEX_OUTPUT_COMPONENTS),
			-1,

			getInt(GL_MAX_GEOMETRY_INPUT_COMPONENTS),
			getInt(GL_MAX_GEOMETRY_OUTPUT_COMPONENTS),
			getInt(GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS),

			getInt(GL_MAX_FRAGMENT_INPUT_COMPONENTS),
			-1,
			-1
		}
	);
	std::cout << "\n";
	std::cout << "Shader Storage Buffer\n";
	ShowTable(
		3, (std::string[]) {
			"Vert",
			"Geom",
			"Frag",
		},
		1, (std::string[]) {
			"SSB Blocks",
		},
		10, 4,
		(int []) {
			getInt(GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS),
			getInt(GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS),
			getInt(GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS),
		}
	);
	ShowTable(
		1, (std::string[]) {
			"",
		},
		1, (std::string[]) {
			"SSB Size",
		},
		8, 10,
		(int []) {
			getInt(GL_MAX_SHADER_STORAGE_BLOCK_SIZE),
		}
	);
	std::cout << "\n";
	ShowTextureLimits();
	std::cout << "\n";
	ShowVertexLimits();
	std::cout << "\n";
}

void OpenGL::ShowBufferInfo()
{
	std::cout << "OpenGL Buffer\n";
	std::cout << "  Array Binding " << getInt(GL_VERTEX_ARRAY_BINDING);

	//	OpenGL >= 4.3
	std::cout << "  Binding Divisor " << getInt(GL_VERTEX_BINDING_DIVISOR);
	std::cout << "  Binding Offset " << getInt(GL_VERTEX_BINDING_OFFSET);
	std::cout << "  Binding Stride " << getInt(GL_VERTEX_BINDING_STRIDE);
	std::cout << "  Binding Buffer" << getInt(GL_VERTEX_BINDING_BUFFER);
}
