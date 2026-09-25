#ifndef  POLYGON_GRAPHICS_FULL_SHADER_HPP
# define POLYGON_GRAPHICS_FULL_SHADER_HPP

# include "Graphics/Uniform/General/Layout.hpp"
# include "Graphics/Uniform/_Include.hpp"

namespace PolyGonFull
{
class ShaderLayout : public Uniform::Layout
{
	public:
	Uniform::DisplaySize		DisplaySize;
	Uniform::Matrix3x3			View;
	Uniform::Float				Scale;
	public:
	~ShaderLayout();
	ShaderLayout();
};
};

#endif