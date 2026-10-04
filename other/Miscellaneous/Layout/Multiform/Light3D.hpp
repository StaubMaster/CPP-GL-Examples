#ifndef  LAYOUT_MULTIFORM_LIGHT_3D_HPP
# define LAYOUT_MULTIFORM_LIGHT_3D_HPP

# include "Layout/Multiform/View3D.hpp"
# include "Graphics/Multiform/General/Buffer.hpp"

class LayoutMultiformLight3D : public LayoutMultiformView3D
{
	public:
	Multiform::Buffer	Lights;
	public:
	LayoutMultiformLight3D();
};

#endif