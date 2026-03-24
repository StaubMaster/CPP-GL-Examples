#ifndef  POLYGON_GRAPHICS_SHADER_HPP
# define POLYGON_GRAPHICS_SHADER_HPP

# include "Graphics/Shader/Base.hpp"
# include "Graphics/UniformsInclude.hpp"

namespace PolyGon
{
class Shader : public ::Shader::Base
{
	public:
	Uniform::DisplaySize		DisplaySize;
	Uniform::Trans2D			View;
	Uniform::Float				Scale;
	public:
	~Shader();
	Shader();
};
};

#endif