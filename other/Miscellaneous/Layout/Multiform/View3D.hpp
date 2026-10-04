#ifndef  LAYOUT_MULTIFORM_VIEW_3D_HPP
# define LAYOUT_MULTIFORM_VIEW_3D_HPP

# include "Layout/Multiform/Display.hpp"
# include "Graphics/Multiform/TypeDefs/Matrix4x4.hpp"
# include "Graphics/Multiform/TypeDefs/Depth.hpp"
# include "Graphics/Multiform/TypeDefs/Angle.hpp"

class LayoutMultiformView3D : public LayoutMultiformDisplay
{
	public:
	Multiform::Matrix4x4	View;
	Multiform::Depth		Depth;
	Multiform::Angle		FOV;
	public:
	LayoutMultiformView3D();
};

#endif