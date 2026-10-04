#ifndef  LAYOUT_UNIFORM_LIGHT_3D_HPP
# define LAYOUT_UNIFORM_LIGHT_3D_HPP

# include "Layout/Uniform/View3D.hpp"
# include "Graphics/Uniform/General/Buffer.hpp"

class LayoutUniformLight3D : public LayoutUniformView3D
{
	public:
	Uniform::Buffer		Lights;
	public:
	LayoutUniformLight3D();
};

#endif