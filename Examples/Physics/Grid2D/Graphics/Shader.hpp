#ifndef  GRID_2D_GRAPHICS_SHADER_HPP
# define GRID_2D_GRAPHICS_SHADER_HPP

# include "Graphics/Shader/Base.hpp"
# include "Graphics/UniformsInclude.hpp"

namespace Grid2DGraphics
{
struct Shader : public ::Shader::Base
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