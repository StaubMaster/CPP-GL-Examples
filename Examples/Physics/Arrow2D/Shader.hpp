#ifndef  ARROW_2D_SHADER_HPP
# define ARROW_2D_SHADER_HPP

# include "Graphics/Shader/Base.hpp"
# include "Graphics/UniformsInclude.hpp"

namespace Arrow2D
{
class Shader : public ::Shader::Base
{
	public:
	Uniform::WindowBufferSize2D	WindowSize;
	Uniform::Trans2D			View;
	Uniform::Float				Scale;
	public:
	Shader();
};
};

#endif