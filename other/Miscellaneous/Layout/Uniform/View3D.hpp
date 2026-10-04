#ifndef  LAYOUT_UNIFORM_VIEW_3D_HPP
# define LAYOUT_UNIFORM_VIEW_3D_HPP

# include "Layout/Uniform/Display.hpp"
# include "Graphics/Uniform/TypeDefs/Matrix4x4.hpp"
# include "Graphics/Uniform/Depth.hpp"
# include "Graphics/Uniform/TypeDefs/Angle.hpp"

class LayoutUniformView3D : public LayoutUniformDisplay
{
	public:
	Uniform::Matrix4x4		View;
	Uniform::Depth			Depth;
	Uniform::Angle			FOV;
	public:
	LayoutUniformView3D();
};

#endif