#ifndef  GRAPHICS_2D_WIRE_SHADER_HPP
# define GRAPHICS_2D_WIRE_SHADER_HPP

# include "Graphics/Shader/Base.hpp"
# include "Graphics/UniformsInclude.hpp"

namespace Graphics2D
{
namespace Wire
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
};

#endif