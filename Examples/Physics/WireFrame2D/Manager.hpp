#ifndef  WIRE_2D_MANAGER_HPP
# define WIRE_2D_MANAGER_HPP

# include "WireFrame2D/Shader.hpp"
# include "WireFrame2D/Buffer.hpp"

class DirectoryInfo;

namespace Wire2D
{
struct Manager
{
	::Wire2D::Shader	Shader;
	::Wire2D::Buffer	Buffer;

	~Manager();
	Manager();

	void InitExternal(const DirectoryInfo & shaderDir);
//	void InitInternal();

	void GraphicsCreate();
	void GraphicsDelete();

	void Draw();
};
};

#endif