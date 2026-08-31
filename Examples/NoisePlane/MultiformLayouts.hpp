#ifndef  MULTIFORM_LAYOUTS_HPP
# define MULTIFORM_LAYOUTS_HPP

# include "Graphics/Multiform/_Include.hpp"
# include "Graphics/Multiform/General/Layout.hpp"

class MultiformLayoutDisplay : public Multiform::Layout
{
	public:
	Multiform::DisplaySize		DisplaySize;
	public:
	~MultiformLayoutDisplay();
	MultiformLayoutDisplay();
};

class MultiformLayoutView3D : public MultiformLayoutDisplay
{
	public:
	Multiform::Matrix4x4	View;
	Multiform::Depth		Depth;
	Multiform::Angle		FOV;
	public:
	~MultiformLayoutView3D();
	MultiformLayoutView3D();
};

#endif