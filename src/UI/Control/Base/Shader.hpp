#ifndef  UI_CONTROL_SHADER_HPP
# define UI_CONTROL_SHADER_HPP

#include "Graphics/Shader/Base.hpp"

#include "Graphics/UniformsInclude.hpp"



class DirectoryContext;



namespace UI
{

namespace Control
{

class BaseShader : public Shader::Base
{
	public:
		Uniform::WindowBufferSize2D WindowSize;

	public:
		BaseShader(const DirectoryContext & dir);
		~BaseShader();
};

};

};

#endif