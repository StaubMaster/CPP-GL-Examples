#ifndef  WIRE_2D_SHADER_HPP
# define WIRE_2D_SHADER_HPP

# include "Graphics/Shader/Base.hpp"
# include "Graphics/UniformsInclude.hpp"

namespace Wire2D
{
class Shader : public ::Shader::Base
{
	public:
	Uniform::DisplaySize		DisplaySize;
	Uniform::Trans2D			View;
	Uniform::Float				Scale;
	public:
	Shader();
};
};

#endif