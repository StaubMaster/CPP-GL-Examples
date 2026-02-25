#ifndef  PHYSICS_2D_SHADER_POLYGON_HPP
# define PHYSICS_2D_SHADER_POLYGON_HPP

# include "Graphics/Shader/Base.hpp"
# include "Graphics/UniformsInclude.hpp"

namespace Physics2D
{
namespace Shaders
{
class PolyGon : public ::Shader::Base
{
	public:
	Uniform::WindowBufferSize2D	WindowSize;
	Uniform::Trans2D			View;
	Uniform::Float				Scale;
	public:
	~PolyGon();
	PolyGon();
};
};
};

#endif