#ifndef  POLYGON_GRAPHICS_WIRE_SHADER_HPP
# define POLYGON_GRAPHICS_WIRE_SHADER_HPP

# include "Graphics/Uniform/General/Layout.hpp"
# include "Graphics/Uniform/_Include.hpp"

namespace PolyGonWire
{
class ShaderLayout : public Uniform::Layout
{
	public:
	Uniform::DisplaySize		DisplaySize;
//	Uniform::Trans2D			View;
	Uniform::Matrix3x3			View;
	Uniform::Float				Scale;
	public:
	~ShaderLayout();
	ShaderLayout();
};
};

#endif