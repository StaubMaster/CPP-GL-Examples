#ifndef  WAVEFRONT_OBJ_SIMPLE3D_SHADER_HPP
# define WAVEFRONT_OBJ_SIMPLE3D_SHADER_HPP

# include "Graphics/Shader/Base.hpp"
# include "Graphics/UniformsInclude.hpp"

namespace Wavefront
{
namespace Simple3D
{
class Shader : public ::Shader::Base
{
	public:
	Uniform::DisplaySize		DisplaySize;
	Uniform::Trans3D			View;
	Uniform::Depth				Depth;
	Uniform::LInter				ColorToTex;
	Uniform::LInter				ShowLightFactor;

	public:
	Shader();
	~Shader();
};
};
};

#endif
