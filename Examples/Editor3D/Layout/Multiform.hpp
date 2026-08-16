#ifndef  LAYOUT_MULTIFORM_HPP
# define LAYOUT_MULTIFORM_HPP

# include "Graphics/Multiform/Layout.hpp"
# include "Graphics/Multiform/_Include.hpp"

class MultiformLayout : public Multiform::Layout
{
	public:
	Multiform::DisplaySize	DisplaySize;
	Multiform::Matrix4x4	View;
	Multiform::Depth		Depth;
	Multiform::Angle		FOV;
	// LightBuffer
	public:
	~MultiformLayout();
	MultiformLayout();
};

#endif