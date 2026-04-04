#ifndef  POLYGON_GRAPHICS_FULL_SHADER_HPP
# define POLYGON_GRAPHICS_FULL_SHADER_HPP

# include "Graphics/Shader/Base.hpp"
# include "Graphics/UniformsInclude.hpp"
# include "Graphics/Uniform/Matrix3x3.hpp"

namespace PolyGonFull
{
class Shader : public ::Shader::Base
{
	public:
	Uniform::DisplaySize		DisplaySize;
//	Uniform::Trans2D			View;
	Uniform::Matrix3x3			View;
	Uniform::Float				Scale;
	public:
	~Shader();
	Shader();
};
};

#endif