#ifndef  PHYSICS_2D_SHADER_HPP
# define PHYSICS_2D_SHADER_HPP

# include "Graphics/Shader/Base.hpp"
# include "Graphics/UniformsInclude.hpp"

namespace Physics2D
{
class Shader : public ::Shader::Base
{
	public:
	Uniform::WindowBufferSize2D	WindowSize;
	Uniform::Point2D			ViewPos;
	Uniform::Angle2D			ViewRot;
	Uniform::Float1				ViewScale;
	public:
	Shader();
};
};

#endif