#ifndef  WIRE_2D_SHADER_HPP
# define WIRE_2D_SHADER_HPP

# include "Graphics/Shader/Base.hpp"
# include "Graphics/UniformsInclude.hpp"

namespace Wire2D
{
class Shader : public ::Shader::Base
{
	public:
	Uniform::WindowBufferSize2D	WindowSize;
	Uniform::Trans2D			View;
	Uniform::Float1				Scale;
	public:
	Shader();
};
};

#endif