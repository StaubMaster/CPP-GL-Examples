#ifndef  VOXEL_GRAPHICS_LAYOUT_F_HPP
# define VOXEL_GRAPHICS_LAYOUT_F_HPP

# include "Graphics/Attribute/General/Layout.hpp"
# include "Graphics/Attribute/_Include.hpp"

namespace VoxelGraphics
{
	struct LayoutF : public ::Attribute::Layout
	{
		::Attribute::VectorF3	Pos;
		::Attribute::VectorF3	Tex;
		::Attribute::VectorF3	Normal;
		~LayoutF();
		LayoutF();
	};
};

#endif