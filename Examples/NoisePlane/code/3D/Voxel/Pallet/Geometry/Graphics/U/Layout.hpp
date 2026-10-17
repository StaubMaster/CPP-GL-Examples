#ifndef  VOXEL_GRAPHICS_LAYOUT_U_HPP
# define VOXEL_GRAPHICS_LAYOUT_U_HPP

# include "Graphics/Attribute/General/Layout.hpp"
# include "Graphics/Attribute/_Include.hpp"

namespace VoxelGraphics
{
	struct LayoutU : public ::Attribute::Layout
	{
		::Attribute::UInt		Voxel;
		::Attribute::UInt		Texture;
		::Attribute::VectorI3	Chunk;
		~LayoutU();
		LayoutU();
	};
};

#endif