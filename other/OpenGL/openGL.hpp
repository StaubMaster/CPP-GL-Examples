#ifndef  OPEN_GL_HPP
# define OPEN_GL_HPP

# include "openGL.h"

namespace OpenGL
{
	int getInt(unsigned int name);
	int getInt(unsigned int name, unsigned int index);

	void ShowContextInfo();
	void ShowCurrentInfo();

	void ShowGeneralLimits();
	void ShowUniformLimits();
	void ShowTextureLimits();
	void ShowVertexLimits();
	void ShowFragmentLimits();

	void ShowLimits();

	void ShowBufferInfo();

	/*struct Shader
	{
		unsigned int ID;
		bool Valid();
		bool IsBound();
		bool Bind();
		void Create();
		void Delete();
	};*/
	//typedef unsigned int ShaderID;
	/*enum class ShaderType
	{
		Vertex = GL_VERTEX_SHADER,
		Geometry = GL_GEOMETRY_SHADER,
		Fragment = GL_FRAGMENT_SHADER,
	};*/

	
};

#endif