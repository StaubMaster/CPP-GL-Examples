#ifndef  SHADERS_HPP
# define SHADERS_HPP

# include "Graphics/Uniform/General/Layout.hpp"
# include "Graphics/Uniform/_Include.hpp"

class ShaderLayoutDisplay : public Uniform::Layout
{
	public:
	Uniform::DisplaySize	DisplaySize;
	public:
	~ShaderLayoutDisplay();
	ShaderLayoutDisplay();
};

class ShaderLayoutView3D : public ShaderLayoutDisplay
{
	public:
	Uniform::Matrix4x4		View;
	Uniform::Depth			Depth;
	Uniform::Angle			FOV;
	public:
	~ShaderLayoutView3D();
	ShaderLayoutView3D();
};

#endif