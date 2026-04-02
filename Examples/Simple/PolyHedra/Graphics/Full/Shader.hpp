#ifndef  POLYHEDRA_FULL_SHADER_HPP
# define POLYHEDRA_FULL_SHADER_HPP

# include "Graphics/Shader/Base.hpp"
# include "Graphics/UniformsInclude.hpp"
# include "Graphics/Uniform/Matrix4x4.hpp"

namespace PolyHedraFull
{
class Shader : public ::Shader::Base
{
	public:
	Uniform::DisplaySize		DisplaySize;
	Uniform::Matrix4x4			View;
	Uniform::Depth				Depth;
	Uniform::Angle				FOV;
	public:
	~Shader();
	Shader();
};
};

#endif