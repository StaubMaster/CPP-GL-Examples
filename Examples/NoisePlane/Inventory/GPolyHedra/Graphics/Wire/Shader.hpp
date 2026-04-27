#ifndef  POLYHEDRA_WIRE_SHADER_HPP
# define POLYHEDRA_WIRE_SHADER_HPP

# include "Graphics/Shader/Base.hpp"
# include "Graphics/Uniform/_Include.hpp"

namespace PolyHedraWire
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